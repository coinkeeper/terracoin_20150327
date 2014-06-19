// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x92114064, 0xca86a665, 0x7189a665, 0xb49c6265, 0xc15ebb6a, 0x7e5fbb6a, 0xcdf6d46b, 0xce5cda6b,
    0xb596dd6b, 0x31d9de6b, 0xd55cb76c, 0x4f42ed6c, 0x45f91b6c, 0xed2c236c, 0xb5f6a56d, 0xfb5e506d,
    0x729b886e, 0x4ee48f6e, 0xa2976a71, 0xf2c87471, 0x6b997a71, 0xfb450d71, 0xf5bea271, 0x4e10210b,
    0x50a7d972, 0x55ad5672, 0xa5d89473, 0xddd8c273, 0x4a744476, 0x902c5177, 0x45c79278, 0x11ea0a79,
    0x4ee3db79, 0xaa02ec79, 0xfc2e967a, 0x6a90e07a, 0x06ca8b7b, 0x3d88107b, 0xd445617b, 0xc631787c,
    0xc899957c, 0xc7a2a97c, 0xb24a6d7d, 0xb84d787d, 0x55f2a77d, 0x0e3d6f80, 0xc4e0fd80, 0x5a0f9f83,
    0x7e0b1186, 0xfa081186, 0xa33ca78e, 0xad454c90, 0xb7af369b, 0x5eaf369b, 0xa806caa2, 0xec907ea4,
    0x5f974ea6, 0x6af1faac, 0xf55504ac, 0x3c5e1cad, 0x246f2cad, 0xe38334ae, 0x12ecb0af, 0xb8a002b0,
    0xd0543db0, 0x8af873b2, 0x83da77b2, 0xfd7d7cb2, 0xea600fb2, 0x6127ddb2, 0x953ddfb2, 0x03cd1ab2,
    0x99da20b2, 0x5ec831b2, 0x33ad4fb2, 0xafed52b2, 0x2c3d09b2, 0xbb299cb7, 0x488f47b7, 0x79b000b8,
    0x7459b9b8, 0xd0f738b8, 0x2aee48b8, 0x4adf4bb8, 0xff1072bc, 0x1d1b8ebc, 0xf49c9abc, 0x4043bfbc,
    0xfe11eebc, 0x6b8bfcbc, 0x720d20bc, 0xc92728bc, 0x6ecd2fbd, 0x48e864be, 0xe6a255c1, 0x576369c2,
    0xedd697c3, 0x087990c6, 0x0c6dc7c6, 0x3347c7c6, 0xd250c7c6, 0xd66c5ac6, 0x3e6d5ac6, 0xb53907c8,
    0xa73718c9, 0x436cbfca, 0x0fe4dbcb, 0xc2714ccb, 0x71690acc, 0x11fe60cf, 0xc39768d0, 0x96176fd4,
    0xa571dcd4, 0xeae6ffd4, 0x5ee9ffd4, 0x39d09ed5, 0x1bbba8d5, 0xcb412fd5, 0x917857d5, 0xdd1388d9,
    0x5e5e91d9, 0x0a781dd9, 0x44a956d9, 0x231b60d9, 0x7e6ac9da, 0x0817c9da, 0x22d850da, 0x7a6b54da,
    0x312ef4dc, 0x10cb51de, 0x46e1ffdf, 0x47e6ffdf, 0x41331017, 0x5b4b6c18, 0x5d927018, 0x037b9918,
    0x415ef718, 0x67dd0618, 0xedec4e18, 0x91d55418, 0xa6c2bc1b, 0x71c35d02, 0x3749ae1f, 0x6399c81f,
    0x3800dc1f, 0x18691f1f, 0x53166e25, 0x90e4bc25, 0xaa2fd025, 0xf5110425, 0xbb990925, 0x4536732e,
    0x6747732e, 0xea4b732e, 0x32b0952e, 0xf27f962e, 0xbf12bc2e, 0x14d6ee2e, 0xdd49f22e, 0xd591fb31,
    0x582d8332, 0x16d78a32, 0x99a31332, 0x6f731732, 0x66382b32, 0x6c6d4832, 0x573c5132, 0xce30a405,
    0x8c4f2705, 0x115a2705, 0x826df436, 0x2785f436, 0xa2ec643a, 0x2f580b3a, 0x07610b3a, 0xa294d83a,
    0xc4f91a3a, 0xe926653b, 0x6126653b, 0xe0cba73b, 0xe4274e3b, 0x0800bc3c, 0x6880ac3d, 0x73e39d3e,
    0x57c79e3e, 0x6840c43e, 0xc763d43e, 0x6e92f93e, 0x8bb54b3e, 0x02a18e3f, 0x08a18e3f, 0xa635b740,
    0x1faebc40, 0x7725ed40, 0x3ebcfb40, 0x7399a741, 0xaca82241, 0xd3b9a242, 0xe15db742, 0xeafa2d42,
    0x94048d43, 0xd6078d43, 0xda80b843, 0xbb90d943, 0xe2a26c44, 0x84de7444, 0xe0a64144, 0xb20a5344,
    0xad726144, 0x88d36144, 0x13cca445, 0x27f8a545, 0xc3e41145, 0x8ffff445, 0x55dcf845, 0x3ca82345,
    0x81405045, 0x7e980945, 0x68847046, 0x0f2d4c46, 0xba197a47, 0x508bc147, 0x52d23847, 0x7e143b47,
    0x370e5d47, 0x3a52b148, 0xf0afc848, 0x608dea48, 0xab1e0948, 0x7d8e684a, 0x47aad04a, 0xe4d13f4a,
    0xbfa3414a, 0xe1384c4a, 0xea77784b, 0x1595854b, 0x82bba14b, 0x21ff6e4c, 0x496d7b4c, 0x567f1e4c,
    0xd5585e4c, 0x2b38a84d, 0x3fc7bf4d, 0xc1366c4e, 0x1bdcf74e, 0x07228b4f, 0x1545994f, 0x3cdbf14f,
    0xc888284f, 0x2765b150, 0xce62d450, 0x2349dc50, 0x35abee50, 0x00d6be51, 0x5ab11e51, 0xb22a3e51,
    0x1f060c52, 0x3e0d8b52, 0x3aa4d952, 0x91c0e052, 0x8684e652, 0xdaf41752, 0x17c1ea52, 0x5d1b2452,
    0xc4229553, 0x73491753, 0x4d962053, 0x32436a54, 0x190d6f54, 0x6fd68754, 0xd5223054, 0x6af93a54,
    0xb6ea0a55, 0x5ea08b55, 0x1189b055, 0x0f96d855, 0x84b2de55, 0x59c8e455, 0x9373ee55, 0xe452f055,
    0x19450455, 0xfc8f9256, 0x3987a656, 0x261b2056, 0x842d3d56, 0x3c8a7057, 0xce0bb757, 0xa964c257,
    0xfefa6257, 0x1963a158, 0xdfb56659, 0x7dd58e59, 0xb387cc59, 0xcdd70759, 0xf1efbc5a, 0xc773d75a,
    0x29a9735b, 0xc5ba755b, 0x1e907b5b, 0x2e0e595b, 0x96a05a5b, 0xa800765c, 0x9452ea5c, 0x05b0ef5c,
    0x8fb2f05c, 0x25f51b5c, 0x86c1275c, 0x435f515c, 0x48587e5d, 0x2b41d45d, 0xa6004b5d, 0x5cb0575d,
    0x4684605d, 0xa741715e, 0x055eae5e, 0x3437bc5e, 0xc0c9d05e, 0x101ce65e, 0x92bdfd5e, 0x78fb495e,
    0xa10f695f, 0x8a9c6e5f, 0xcfa0855f, 0xebca855f, 0x1d09105f, 0xcb26ae5f, 0x5aedf35f, 0xe7c4205f,
    0x7de1215f, 0x55f8395f, 0xf370f860, 0xfb822b60, 0xaa8f2c60, 0x027d5161, 0x22d25261, 0x442b5661,
    0xceae5961, 0xa3041462, 0xf01acc62, 0xe719e862, 0x44a71c62, 0x48046663, 0xcd3d8763, 0x4e59a263

};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CChainParams::MAIN;
        strNetworkID = "main";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0xba;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0x56;
        vAlertPubKey = ParseHex("04b79d46f177ae69578c2f206be096a22e2de73ad6296ddf9c330faa32b249f63028b039c2cdb7cba0d0b034f66f0c28b8131ec4e6dc9ed67dcedddacdf218f305");
        vCoinbaseDonationPubKey = ParseHex("0404824f90982d1835e21f3cda8f0a14e4dc00df59046e06cc4dcfc47e824b66da36e17483cd4bd48c72fbc5120cafcbd6288bc828f379606e5b534ecbe70b1ecb");
        nCoinbaseDonationStartingTime = 1404777600; // july 8th 2014 00:00
        nDefaultPort = 13333;
        nRPCPort = 13332;
        bnProofOfWorkLimit = ~uint256(0) >> 32;
        nSubsidyHalvingInterval = 1050000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
        //   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
        //     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
        //   vMerkleTree: 4a5e1e
        const char* pszTimestamp = "June 4th 1978 - March 6th 2009 ; Rest In Peace, Stephanie.";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1351242683;
        genesis.nBits    = 0x1d00ffff;
        genesis.nNonce   = 2820375594;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000000804bbc6a621a9dbb564ce469f492e1ccf2d70f8a6b241e26a277afa2"));
        assert(genesis.hashMerkleRoot == uint256("0x0f8b09f93803b067580c16c3f3a6aaa901be06ad892cea9f02d8a4f93628f196"));

        vSeeds.push_back(CDNSSeedData("seed1.terracoin.org", "seed1.net.terracoin.org"));
        vSeeds.push_back(CDNSSeedData("seed2.terracoin.org", "seed2.net.terracoin.org"));
        vSeeds.push_back(CDNSSeedData("seed3.terracoin.org", "seed3.net.terracoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(0);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(128);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = false;
        fRequireStandard = true;
        fRPCisTestNet = false;
        fMineBlocksOnDemand = false;
    }
};
static CMainParams mainParams;

//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CChainParams::TESTNET;
        strNetworkID = "test";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0xba;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0x56;
        vAlertPubKey = ParseHex("0415e63deb4a13fc9aa182121fd8b3cc582c205f57dabdf291b71e2c298060cec4f06bc3806485f45f19d07e48c1e1874fbab82ad7b8420866914ee00aeac75291");
        vCoinbaseDonationPubKey = ParseHex("04326eef42c58f51526a7ce235d83f5ff7f1b2fc9e33a8f4d7b0bf5aa105b301b0bdcdf70b5cf44d85cad17864467833ca833e58487f705a2cbe3a446510b892c8");
        nCoinbaseDonationStartingTime = 1403178387;

        nDefaultPort = 23333;
        nRPCPort = 23332;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1354965534;
        genesis.nNonce = 1178774204;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000000d64b490e447fb522682bfa6bcb27886ed1a94d7a4856fb92ab130875"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed1.terracoin.org", "seed1.net.terracoin.org"));
        vSeeds.push_back(CDNSSeedData("seed3.terracoin.org", "seed3.net.terracoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fRPCisTestNet = true;
        fMineBlocksOnDemand = false;
    }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xba;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0xea;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 23444;
        strDataDir = "regtest";

/*
        FILE *h_log = fopen("/tmp/genesis.block.log", "a+");
        if (h_log) {
            fprintf(h_log, " nTime: %u\n", genesis.nTime);
            fprintf(h_log, "nNonce: %u\n", genesis.nNonce);
            fprintf(h_log, "  hash: %s\n", genesis.GetHash().ToString().c_str());
            fclose(h_log);
        }
*/
        assert(hashGenesisBlock == uint256("0x5424a2e7fce169e6b9841d0b543a9c53ba111f3b31921b9fd768baa8ead4a8d2"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fRPCisTestNet = true;
        fMineBlocksOnDemand = true;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
