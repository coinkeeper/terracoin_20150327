#include "alert.h"
#include "bitcoinrpc.h"
#include "checkpoints.h"
#include "db.h"
#include "txdb.h"
#include "net.h"
#include "init.h"
#include "ui_interface.h"
#include "checkqueue.h"
#include "chainparams.h"
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;
using namespace boost;

/**
 * @brief Average block duration over (up to) given block count.
 * @return int64 -1 on error/malformed input average block duration otherwise.
 */
int64 GetAveragedBlockDuration(const CBlockIndex *blkIdx, int64 blockCount) {
    if (blkIdx == NULL || blockCount == 0) {
        return (-1);
    }

    const CBlockIndex *curBlk = blkIdx;
    int i = 1;
    for (i=1 ; blkIdx && i<=blockCount ; i++) {
        if (blkIdx->pprev == NULL) {
            break;
        }
        if (blkIdx->pprev->nHeight == 0) {
            if (i>1) { i--; }
            break;
        }
        blkIdx = blkIdx->pprev;
    }

    return ( (curBlk->GetBlockTime() - blkIdx->GetBlockTime()) / i );
}

/**
 * @brief time (seconds) between given block and givenblock-blockCount
 */
int64 GetBlockRangeDuration(const CBlockIndex *blkIdx, int64 blockCount) {
    if (blkIdx == NULL || blockCount == 0) {
        return (-1);
    }

    const CBlockIndex *curBlk = blkIdx;
    for (int i = 0; blkIdx && i < blockCount ; i++) {
        blkIdx = blkIdx->pprev;
    }
    assert(blkIdx);

    return ( curBlk->GetBlockTime() - blkIdx->GetBlockTime() );
}

/**
 * @brief soon (Aug 2013) to be deprecated filter supposed to eliminate malicious ntime manipulations.
 * @details instead of using a larger blocks window to get effective hashrate, this used only the last two blocks, leading to this :(
 * @note obviously kept active for integrity while client redownloads earlier blocks.
 */
unsigned int static GetEmaNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock) {
    int64 block_durations[2160];
    float alpha = 0.09; // closer to 1.0 = faster response to new values
    if (pindexLast->nHeight > 110322) {
        alpha = 0.06;
    }
    float accumulator = 120;
    const int64 perBlockTargetTimespan = 120; // two mins between blocks

    unsigned int nProofOfWorkLimit = Params().ProofOfWorkLimit().GetCompact();
    if (pindexLast == NULL)
        return nProofOfWorkLimit;

    if (pblock->nTime > pindexLast->nTime + perBlockTargetTimespan*10) {
        if (TestNet()) {
            printf("TESTNET: allowing min-difficulty mining.\n");
            return nProofOfWorkLimit;
        } else if (pindexLast->nHeight < 175000) {
            // livenet ; will allow diff/2 unless exiting from apr 9th 2013 stalled state:
            CBigNum bnNew;
            bnNew.SetCompact(pindexLast->nBits);

            if (pindexLast->nHeight> 101631 && pindexLast->nHeight < 103791) {
                //insane difficulty drop ; until the network gets big enough, and not abused anymore
                bnNew *= 10;
            } else {
                // half the last diff, sucks too, but with a big enough network,
                // no block should take 20 minutes to be mined!
                bnNew *= 2;
                printf("RETARGET: artificially lowered diff ; hard time mining current block...\n");
            }

            // super ugly way to never, ever return diff < 5254:
            if (pindexLast->nHeight > 104290) {
                CBigNum fiveThousandsLimit;
                fiveThousandsLimit.SetCompact(0x1b0c7898);
                if (bnNew > fiveThousandsLimit) {
                    bnNew = fiveThousandsLimit;
                }
            }

            if (bnNew > Params().ProofOfWorkLimit())
                bnNew = Params().ProofOfWorkLimit();

            printf("Before: %08x  %s\n", pindexLast->nBits, CBigNum().SetCompact(pindexLast->nBits).getuint256().ToString().c_str());
            printf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());

            return (bnNew.GetCompact());
        }
    }

    // collect last 3 days (30*24*3=2160) blocks durations:
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < 2160 ; i++) {
        block_durations[2159 - i] = pindexFirst->GetBlockTime() - pindexFirst->pprev->GetBlockTime();

        if (pindexLast->nHeight > 110322) {
            // slow down difficulty decrease even more,
            // also limit the effect of future nTime values (actually annihilates them):
            if (block_durations[2159 - i] > (1.5 * perBlockTargetTimespan) ) {
                block_durations[2159 - i] = 1.5 * perBlockTargetTimespan;
            }

            // slow down difficulty increase:
            if ((block_durations[2159 - i] >= 0) && (block_durations[2159 - i] < (perBlockTargetTimespan / 2)) ) {
                block_durations[2159 - i] = perBlockTargetTimespan / 2;
            }
        }

        if (block_durations[2159 - i] < 0 && pindexLast->nHeight > 104290) {
            block_durations[2159 - i] = perBlockTargetTimespan;
        }
        if (TestNet()) {
            printf("EMA: height=%d duration=%"PRI64d"\n", pindexFirst->nHeight, block_durations[2159 - i]);
        }
        pindexFirst = pindexFirst->pprev;
    }

    // compute exponential moving average block duration:
    for (int i=0; i<2160 ; i++) {
        accumulator = (alpha * block_durations[i]) + (1 - alpha) * accumulator;

        if (TestNet()) {
            CBlockIndex *blk = FindBlockByHeight((int) pindexLast->nHeight - (2159 - i));
            if (blk) {
                // csv-like logging ; grep/sed 'EMA424242:' for easy plotting
                // EMA<last_height>:height,diff,duration,ema
                printf("EMA%d:%d,%f,%"PRI64d",%f\n", pindexLast->nHeight, pindexLast->nHeight - (2159 - i), GetDifficulty(blk), block_durations[i], accumulator);
            }
        }
    }

    int64 nActualTimespan = accumulator;
    if (TestNet()) {
        printf("GetEmaNextWorkRequired RETARGET nActualTimespan = %"PRI64d"  before bounds\n", nActualTimespan);
    }

    if (nActualTimespan < perBlockTargetTimespan / 2)
        nActualTimespan = perBlockTargetTimespan / 2;
    if (pindexLast->nHeight > 110322) {
        // symetrical adjustments, both sides:
        if (nActualTimespan > perBlockTargetTimespan * 2) {
            nActualTimespan = perBlockTargetTimespan * 2;
        }
    } else {
        if (nActualTimespan > perBlockTargetTimespan * 4) {
            nActualTimespan = perBlockTargetTimespan * 4;
        }
    }

    // Retarget
    CBigNum bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= perBlockTargetTimespan;

    // temporary, super ugly way to never, ever return diff < 5254:
    if (pindexLast->nHeight > 104290) {
        CBigNum fiveThousandsLimit;
        fiveThousandsLimit.SetCompact(0x1b0c7898);
        if (bnNew > fiveThousandsLimit) {
            bnNew = fiveThousandsLimit;
        }
    }

    if (bnNew > Params().ProofOfWorkLimit())
        bnNew = Params().ProofOfWorkLimit();

    if (TestNet()) {
        printf("nTargetTimespan = %"PRI64d" nActualTimespan = %"PRI64d"\n", perBlockTargetTimespan, nActualTimespan);
        printf("Before: %08x  %s\n", pindexLast->nBits, CBigNum().SetCompact(pindexLast->nBits).getuint256().ToString().c_str());
        printf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());
    }

    return bnNew.GetCompact();
}

/**
 * @brief separate testnet retargetting.
 * @details retargets every X blocks with timings from last Y blocks
 * @note this is testnet, made to change every now and then.
 */
unsigned int static GetTestnetBasicNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock) {
    unsigned int nProofOfWorkLimit = Params().ProofOfWorkLimit().GetCompact();

    // genesis block:
    if (pindexLast == NULL) {
        return (nProofOfWorkLimit);
    }

    // testnet uses 20x times less blocks than livenet:
    const int64 retargetBlockCountInterval = 10; // retarget every 108 blocks (2160 for livechain)
    const int64 lookupBlockCount = 10; // past blocks to use for timing (2160 for livenet)

    const int64 retargetTimespan = 120 * retargetBlockCountInterval; // 2 minutes per block
    const int64 retargetVsInspectRatio = lookupBlockCount / retargetBlockCountInterval;

    // non-retargetting block: keep same diff or (testnet) special min diff:
    if ((pindexLast->nHeight+1) % retargetBlockCountInterval != 0 || (pindexLast->nHeight) < lookupBlockCount) {
        if (pindexLast->nHeight > 660) {
            // testnet special rule: new block's timestamp is 2hours+ older than previous
            if (pblock->nTime > pindexLast->nTime + 7200) {
                return (nProofOfWorkLimit);
            }
        } else {
            // testnet special rule: new block's timestamp is 20mins+ older than previous
            if (pblock->nTime > pindexLast->nTime + 1200) {
                return (nProofOfWorkLimit);
            }
        }

        // outside retarget, keep same target:
        return (pindexLast->nBits);
    }

    // retargetting block:
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < lookupBlockCount ; i++) {
        pindexFirst = pindexFirst->pprev;
    }
    assert(pindexFirst);

    int64 nActualTimespan = pindexLast->GetBlockTime() - pindexFirst->GetBlockTime();
    nActualTimespan = nActualTimespan / retargetVsInspectRatio;

    // limit target adjustments:
    printf("RETARGET nActualTimespan = %"PRI64d"  before bounds\n", nActualTimespan);
    if (nActualTimespan < retargetTimespan / 4) {
        nActualTimespan = retargetTimespan / 4;
    }
    if (nActualTimespan > retargetTimespan * 4) {
        nActualTimespan = retargetTimespan * 4;
    }

    // new target:
    CBigNum bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= retargetTimespan;

    if (bnNew > Params().ProofOfWorkLimit()) {
        bnNew = Params().ProofOfWorkLimit();
    }

    printf("RETARGET height=%d nTargetTimespan = %"PRI64d" nActualTimespan = %"PRI64d"\n", pindexLast->nHeight, retargetTimespan, nActualTimespan);
    printf("RETARGET Before: %08x  %s\n", pindexLast->nBits, CBigNum().SetCompact(pindexLast->nBits).getuint256().ToString().c_str());
    printf("RETARGET  After: %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());

    return (bnNew.GetCompact());
}

/**
 * @brief target required by next block.
 * @details retargets every 180 blocks with timings from last 2160 blocks.
 */
unsigned int static GetBasicNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock) {
    unsigned int nProofOfWorkLimit = Params().ProofOfWorkLimit().GetCompact();

    // genesis block:
    if (pindexLast == NULL) {
        return (nProofOfWorkLimit);
    }

    const int64 retargetBlockCountInterval = 2160; // retarget every 2160 blocks
    const int64 lookupBlockCount = 2160; // past blocks to use for timing
    const int64 retargetTimespan = 120 * retargetBlockCountInterval; // 2 minutes per block
    const int64 retargetVsInspectRatio = lookupBlockCount / retargetBlockCountInterval; // currently 12

    // non-retargetting block: keep same diff:
    if ((pindexLast->nHeight+1) % retargetBlockCountInterval != 0 || (pindexLast->nHeight) < lookupBlockCount) {
        // outside retarget, keep same target:
        return (pindexLast->nBits);
    }

    // retargetting block, capture timing over last lookupBlockCount blocks:
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < lookupBlockCount ; i++) {
        pindexFirst = pindexFirst->pprev;
    }
    assert(pindexFirst);
    int64 nActualTimespan = pindexLast->GetBlockTime() - pindexFirst->GetBlockTime();
    nActualTimespan = nActualTimespan / retargetVsInspectRatio;

    // limit target adjustments:
    printf("RETARGET nActualTimespan = %"PRI64d"  before bounds\n", nActualTimespan);
    if (nActualTimespan < retargetTimespan / 4) {
        nActualTimespan = retargetTimespan / 4;
    }
    if (nActualTimespan > retargetTimespan * 4) {
        nActualTimespan = retargetTimespan * 4;
    }

    // new target:
    CBigNum bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= retargetTimespan;

    // during the switchover from EMA retargetting to static 2160 retargetting:
    // temporary, low diff limit: 17.4k self deactivating at height 182000
    // (for first retarget only)
    if (pindexLast->nHeight < 183000) {
        CBigNum seventeenThousandsLimit;
        seventeenThousandsLimit.SetCompact(0x1b03bf8b);
        if (bnNew > seventeenThousandsLimit) {
            bnNew = seventeenThousandsLimit;
        }
    }

    // temporary, super ugly way to never, ever return diff < 5254,
    // just in the case something really bad happens
    // self-deactivate at block 220000
    if (pindexLast->nHeight < 220000) {
        CBigNum fiveThousandsLimit;
        fiveThousandsLimit.SetCompact(0x1b0c7898);
        if (bnNew > fiveThousandsLimit) {
            bnNew = fiveThousandsLimit;
        }
    }

    // min diff:
    if (bnNew > Params().ProofOfWorkLimit()) {
        bnNew = Params().ProofOfWorkLimit();
    }

    printf("RETARGET height=%d nTargetTimespan = %"PRI64d" nActualTimespan = %"PRI64d"\n", pindexLast->nHeight, retargetTimespan, nActualTimespan);
    printf("RETARGET Before: %08x  %s\n", pindexLast->nBits, CBigNum().SetCompact(pindexLast->nBits).getuint256().ToString().c_str());
    printf("RETARGET  After: %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());

    return (bnNew.GetCompact());
}

unsigned int GetTerracoinNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock)
{
    if (TestNet()) {
        return (GetTestnetBasicNextWorkRequired(pindexLast, pblock));
    }

    unsigned int    nProofOfWorkLimit   = Params().ProofOfWorkLimit().GetCompact();

    // Genesis block
    if (pindexLast == NULL)
        return nProofOfWorkLimit;

    // back to a basic retargetting, over longer periods:
    if (pindexLast->nHeight > 181200) {
        return (GetBasicNextWorkRequired(pindexLast, pblock));
    }

    if (TestNet() && pindexLast->nHeight > 5182) {
        return (GetEmaNextWorkRequired(pindexLast, pblock));
    } else if (pindexLast->nHeight > 101631) {
        // activate ema after block 101631
        return (GetEmaNextWorkRequired(pindexLast, pblock));
    }

    // Only change once per interval
    if ((pindexLast->nHeight+1) % Params().Ninterval() != 0)
    {
        return pindexLast->nBits;
    }

    // Go back by what we want to be 1 hour worth of blocks:
    int nBlocksLookupRange = Params().Ninterval() - 1;
    if (TestNet()) {
        if (pindexLast->nHeight > 89) {
            nBlocksLookupRange = Params().Ninterval();
        }
    } else {
        // failed attempt ; amplified spikes effects...
        if (pindexLast->nHeight > 99988) {
            nBlocksLookupRange = Params().Ninterval() * 24;
        }
    }
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < nBlocksLookupRange ; i++)
        pindexFirst = pindexFirst->pprev;
    assert(pindexFirst);

    // Limit adjustment step
    int64 nActualTimespan = pindexLast->GetBlockTime() - pindexFirst->GetBlockTime();
    if (pindexLast->nHeight > 101908) {
        nActualTimespan = nActualTimespan / 3;
    } else if (pindexLast->nHeight > 99988) {
        nActualTimespan = nActualTimespan / 24;
    }
    printf("  nActualTimespan = %"PRI64d"  before bounds\n", nActualTimespan);
    if (nActualTimespan < Params().TargetTimespan() / 4)
        nActualTimespan = Params().TargetTimespan() / 4;
    if (nActualTimespan > Params().TargetTimespan() * 4)
        nActualTimespan = Params().TargetTimespan() * 4;

    // Retarget
    CBigNum bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= Params().TargetTimespan();

    if (bnNew > Params().ProofOfWorkLimit())
        bnNew = Params().ProofOfWorkLimit();

    /// debug print
    printf("GetNextWorkRequired RETARGET\n");
    printf("nTargetTimespan = %"PRI64d"    nActualTimespan = %"PRI64d"\n", Params().TargetTimespan(), nActualTimespan);
    printf("Before: %08x  %s\n", pindexLast->nBits, CBigNum().SetCompact(pindexLast->nBits).getuint256().ToString().c_str());
    printf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());

    return (bnNew.GetCompact());
}


