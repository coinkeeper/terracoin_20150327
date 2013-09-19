// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x92114064, 0xca86a665, 0x7189a665, 0xb49c6265, 0x4e420a67, 0xc15ebb6a, 0x7e5fbb6a, 0x7f7cd26b,
    0xcdf6d46b, 0xce5cda6b, 0xb596dd6b, 0x31d9de6b, 0x3bca0e6c, 0x2080aa6c, 0x3582aa6c, 0x505d116c,
    0xd55cb76c, 0x22fc166c, 0xa175e86c, 0xe74deb6c, 0x4f42ed6c, 0x45f91b6c, 0xed2c236c, 0x9e74286c,
    0xa94f286c, 0x168b096c, 0x7ab86f6d, 0x69d2816d, 0xf2d0906d, 0xb1e1a36d, 0xb5f6a56d, 0xbe9fbe6d,
    0x0998c96d, 0xb7ad446d, 0x488c4d6d, 0x0e2a4f6d, 0x4da6506d, 0xfb5e506d, 0xc1a45d6d, 0xc8b15d6d,
    0xa3245d6d, 0x729b886e, 0x071e8b6e, 0x4ee48f6e, 0x1500a16f, 0x877fa16f, 0x8611ce6f, 0x4842d770,
    0x4c42d770, 0x62407a01, 0xa2976a71, 0xf2c87471, 0x50157571, 0x6b997a71, 0xfb450d71, 0xf5bea271,
    0x4e10210b, 0x059e220b, 0x5200230b, 0x50a7d972, 0x5d16d972, 0x3bb1f972, 0x1e874c72, 0xd6a44d72,
    0x55ad5672, 0xc0bf5672, 0x42467373, 0xa5d89473, 0xec6ec073, 0xbda1c173, 0xddd8c273, 0x0d19ca73,
    0xf09ecc73, 0x96fdd973, 0x638b0c74, 0xc6d6c774, 0x22bbe474, 0x30ede974, 0xe4193574, 0xfbab6775,
    0x220b5075, 0x40a8b776, 0x6ca9b776, 0x0b881576, 0x05cff476, 0x06cff476, 0x4a744476, 0x0d385c76,
    0xb5608377, 0x0253a277, 0x902c5177, 0x24c80e78, 0xf1cc0e78, 0x45c79278, 0x062bca01, 0x152eca01,
    0xdb870678, 0x11ea0a79, 0x4ee3db79, 0xaa02ec79, 0xa68c6a7a, 0xfc2e967a, 0xd733967a, 0x6a90e07a,
    0x2623e87a, 0x3139f67a, 0x06ca8b7b, 0x9eab957b, 0x3d88107b, 0xd404a37b, 0xc1d1e97b, 0xcbae1c7b,
    0x8d97220c, 0x17f0220c, 0xe998347b, 0xd445617b, 0x971a767c, 0xc631787c, 0x10d07f7c, 0xf6280d7c,
    0x43a8947c, 0xb590957c, 0xc899957c, 0x6f2c957c, 0xc7a2a97c, 0x1311aa7c, 0x2a05aa7c, 0x2b2cbb7c,
    0xe3b6e47c, 0xdf564e7c, 0xb24a6d7d, 0xe517787d, 0x4b2d787d, 0xb84d787d, 0xc211797d, 0x83f67d7d,
    0x4af0a77d, 0x55f2a77d, 0xd5f8a77d, 0x136c417d, 0x720a4e7d, 0xd8084e7d, 0x0a3d6f80, 0x0e3d6f80,
    0xc4e0fd80, 0xdde54780, 0x829bb982, 0xb545cc82, 0xce442b82, 0x5a0f9f83, 0x676caa84, 0x7e0b1186,
    0xfa081186, 0x94b3a988, 0xa3a46389, 0x0148258a, 0x0bd09e8d, 0xdfd49e8d, 0x98d99e8d, 0x2d7e770e,
    0xa821818e, 0xc12e818e, 0x6020a68e, 0xc33ba78e, 0xa33ca78e, 0xc1a18890, 0xad454c90, 0x79503492,
    0xaedce593, 0x9ef7e697, 0x48ac4a97, 0xb7af369b, 0x5eaf369b, 0x5389409e, 0x845fe09f, 0xa806caa2,
    0x6b96e2a2, 0xf6a40ba3, 0x95eb8ea3, 0xec907ea4, 0x0ae07fa4, 0xd403b5a6, 0x5f974ea6, 0x3c9b90a8,
    0x5a1324ab, 0xd7cf24ab, 0x464f25ab, 0xe44405ab, 0x154e62ab, 0x6af1faac, 0xf55504ac, 0xd4ac02ad,
    0x06c6f8ad, 0x44d8fead, 0x3c5e1cad, 0x246f2cad, 0x37522cad, 0xdc5639ad, 0xd13741ad, 0x9b9242ad,
    0x752e55ad, 0x601766ae, 0xfb6172ae, 0x6e0073ae, 0xff237eae, 0x30bd03ae, 0xd50c30ae, 0xe38334ae,
    0xfd3134ae, 0xdcdc3bae, 0xeba858ae, 0xf3d990af, 0x12ecb0af, 0xa6992baf, 0x5ebf70b0, 0x129974b0,
    0xb8a002b0, 0xfba3e3b0, 0x9e8419b0, 0xe6371cb0, 0x79182eb0, 0xd0543db0, 0x718a09b0, 0xd49a09b0,
    0xf5525cb0, 0x842712b1, 0xfec453b1, 0x8af873b2, 0x72510bb2, 0x83da77b2, 0xfd7d7cb2, 0x4a7f7eb2,
    0xea600fb2, 0x9d1b10b2, 0x9b0710b2, 0x3feaceb2, 0x6127ddb2, 0xff19deb2, 0xa327dfb2, 0x953ddfb2,
    0x8e08dfb2, 0x2b7218b2, 0x6e53fcb2, 0x03cd1ab2, 0xb2de1bb2, 0x7eac20b2, 0x99da20b2, 0x628824b2,
    0xe97631b2, 0x5ec831b2, 0x879407b2, 0x3ad94cb2, 0x33ad4fb2, 0xafed52b2, 0xe1b65ab2, 0x518a09b2,
    0x7d9d5cb2, 0x39a35cb2, 0x2c3d09b2, 0xca566ab4, 0xe11d6cb4, 0x43e8d6b4, 0x4be8d6b4, 0xcad1f8b4,
    0xb8f3f8b4, 0x10f4f8b4, 0x57f4f8b4, 0x87f7f8b4, 0xcb48fdb4, 0x83a585b6, 0xe78fefb6, 0x5b9cefb6,
    0x49a647b6, 0x52db87b7, 0xbb299cb7, 0xe90d9db7, 0x0da09db7, 0x22349db7, 0x2fa6ebb7, 0x9a24ecb7,
    0x1d29ecb7, 0x1da43eb7, 0xc6e83eb7, 0x488f47b7, 0x79b000b8, 0x7459b9b8, 0x7959b9b8, 0x6b3e04b8,
    0xd0f738b8, 0x2aee48b8, 0x372f07b8, 0x432f07b8, 0x4adf4bb8, 0x0cd94eb8, 0xc38c60b8, 0x74e560b8,
    0x97060cb9, 0x028703b9, 0x137f82ba, 0x064b12ba, 0x16a700bc, 0xff1072bc, 0x0e087ebc, 0xaa6281bc,
    0xeba08abc, 0x1d1b8ebc, 0xf49c9abc, 0x6f84a2bc, 0x4724a2bc, 0xa723babc, 0x4043bfbc, 0xbdcbc0bc,
    0xfe11eebc, 0x66bfeebc, 0x6b8bfcbc, 0x720d20bc, 0xc92728bc, 0xc1ce06bc, 0xb23a06bc, 0x6ecd2fbd,
    0x48e864be, 0x10def1c0, 0x020e97c1, 0x070e97c1, 0x08d210c1, 0x6e1654c1, 0xe6a255c1, 0x576369c2,
    0x2b2084c2, 0xed21b7c2, 0x810be4c2, 0xd598e4c2, 0xdc6a01c3, 0xedd697c3, 0xdd31d0c3, 0x0796f2c3,
    0xc51f1cc3, 0xb2752ec3, 0x23c25bc3, 0x95b657c5, 0x02d10ec6, 0x497990c6, 0x087990c6, 0x0c6dc7c6,
    0x7176c7c6, 0x3347c7c6, 0xd250c7c6, 0x8272c8c6, 0x07e932c6, 0x8d9a54c6, 0xd66c5ac6, 0x3e6d5ac6,
    0xa9ce10c7, 0x2380f7c7, 0x299330c7, 0x907e68c8, 0x943807c8, 0xb53907c8, 0x533907c8, 0x023e07c8,
    0xe83e07c8, 0x373e07c8, 0xf9c6bfc9, 0xc84eebc9, 0xa73718c9, 0xca177fca, 0x436cbfca, 0xc27214cb,
    0x8a81dbcb, 0x0fe4dbcb, 0xc2714ccb, 0x71690acc, 0x83537ccc, 0x047233cc, 0x7e03fdcf, 0x11fe60cf,
    0x048268d0, 0xc39768d0, 0x600f7cd0, 0xd756a9d0, 0x2e6e58d0, 0x9e9887d1, 0xf970efd1, 0xc95053d2,
    0x0e0793d3, 0x0f0793d3, 0x100793d3, 0x96176fd4, 0xa1447cd4, 0x5902b2d4, 0xa571dcd4, 0xeae6ffd4,
    0x1ae7ffd4, 0x5ee9ffd4, 0xeaedffd4, 0x0af2ffd4, 0x5cfcffd4, 0xc72fffd4, 0x4d7d40d4, 0x3e245ad4,
    0x7fb172d5, 0x81d09ed5, 0x82d09ed5, 0x39d09ed5, 0x1bbba8d5, 0x164af0d5, 0xda01fad5, 0x2a2b2fd5,
    0xcb412fd5, 0x336f8a02, 0x917857d5, 0xe14b63d5, 0x25a36cd8, 0x49a6c1d8, 0xa19e31d8, 0x9eee6ad9,
    0x840a73d9, 0xdd1388d9, 0x5e5e91d9, 0xdea293d9, 0x938f17d9, 0xab74f8d9, 0x0a781dd9, 0xf9802cd9,
    0x44a956d9, 0x231b60d9, 0xafce00da, 0x7e6ac9da, 0x0817c9da, 0x029916da, 0x22d850da, 0x7a6b54da,
    0x61ff8edb, 0x0629e9dc, 0x312ef4dc, 0xaf92f5dc, 0x57dfce02, 0x02317fdd, 0x7cd407dd, 0xee1d48de,
    0x10cb51de, 0xbdd0cfdf, 0x46e1ffdf, 0x47e6ffdf, 0x49e6ffdf, 0x41331017, 0x76195c17, 0x2f660a18,
    0x47720a18, 0x8c386c18, 0x5b4b6c18, 0xc3326f18, 0x5d927018, 0x6cbb9618, 0x037b9918, 0xc2b69e18,
    0x3d3eba18, 0x160abb18, 0xf9f9bc18, 0x6486df18, 0x415ef718, 0x4553fb18, 0x89790518, 0x1ce33d18,
    0x67dd0618, 0xed524318, 0xa3bc4b18, 0xedec4e18, 0x91d55418, 0xe20a7019, 0xb8a3ad19, 0x552c5819,
    0xa6c2bc1b, 0x90762e1b, 0xa8c7371b, 0x71c35d02, 0x67c75e02, 0x1593101f, 0x32c2101f, 0x041eac1f,
    0x3749ae1f, 0x5634af1f, 0x6399c81f, 0x3800dc1f, 0x3c00dc1f, 0x18691f1f, 0xeb6a1f1f, 0xcdcd351f,
    0x4723f924, 0x53166e25, 0x40a07125, 0x85e38225, 0xa2188b25, 0xb1370e25, 0x8963bb25, 0x90e4bc25,
    0x5c931325, 0x0772c125, 0xaa2fd025, 0x3f19e525, 0xf5110425, 0x138d4e25, 0x048d4e25, 0xb2bc4e25,
    0x3de64e25, 0x06564e25, 0x31960925, 0xbb990925, 0xf31d6325, 0xb1e16c26, 0xa2448429, 0x5c798729,
    0x2799ea29, 0x572f0a2e, 0x4536732e, 0x6747732e, 0xea4b732e, 0x1f18802e, 0x32b0952e, 0xe67f962e,
    0xf27f962e, 0x9d04ad2e, 0x1f40b72e, 0xbf12bc2e, 0xa69abf2e, 0x1fa6bf2e, 0x3e8c132e, 0x14d6ee2e,
    0xdd49f22e, 0xcee8f42e, 0x76eaf42e, 0x4015f92e, 0xc71ef92e, 0xa2501c2e, 0x0c16042e, 0xfe173f2e,
    0x9173092e, 0xd591fb31, 0x8b6a3031, 0x8e773031, 0x33973031, 0x59e63131, 0xe5f04a31, 0xc25e0032,
    0xd31f7132, 0x582d8332, 0xbbc98832, 0x16d78a32, 0xd400a032, 0x17daa532, 0x99a31332, 0x6358c832,
    0x6f731732, 0x66382b32, 0x6c6d4832, 0x573c5132, 0xd5625232, 0x5ba78705, 0x41368705, 0xa0a28a05,
    0x7fbb8a05, 0x56d58a05, 0xf6dc8a05, 0xe8f88a05, 0x09d49605, 0xce30a405, 0x8c4f2705, 0x115a2705,
    0xd98fd036, 0x92e9d636, 0xc003d636, 0xe21de336, 0x826df436, 0x2785f436, 0x31bff536, 0x845efc36,
    0xcf024405, 0x31ed4605, 0xd9474f05, 0xa2ec643a, 0xb7530b3a, 0x2f580b3a, 0x07610b3a, 0xa294d83a,
    0xf24bf93a, 0xc4f91a3a, 0xccbe3b3a, 0xd20e653b, 0x8618653b, 0xaf18653b, 0xdb18653b, 0xe926653b,
    0x2826653b, 0x6126653b, 0xe0cba73b, 0x1dc8ae3b, 0x91020905, 0x57460905, 0xe4274e3b, 0x0800bc3c,
    0x0490a43d, 0x6880ac3d, 0xb6f7133d, 0x73e39d3e, 0x57c79e3e, 0x7152a33e, 0x20fac23e, 0x6840c43e,
    0xc951c93e, 0xc763d43e, 0x8b7cf53e, 0x6e92f93e, 0x7cc0ff3e, 0x8bb54b3e, 0x02a18e3f, 0x08a18e3f,
    0xea968140, 0xa635b740, 0x1faebc40, 0x7425ed40, 0x7725ed40, 0x3ebcfb40, 0x42bcfb40, 0x7399a741,
    0x0c5cba41, 0x43341841, 0xaca82241, 0xd3b9a242, 0xb61bac42, 0xe15db742, 0x6d43bb42, 0xa44fbd42,
    0xaa35d142, 0xfac71942, 0xeafa2d42, 0x94048d43, 0xd6078d43, 0x6ba3a543, 0xda80b843, 0xa42ebe43,
    0xbb90d943, 0xf2d9e643, 0x962a3443, 0x09203743, 0xdf2e3743, 0xe2a26c44, 0x792f7144, 0x84de7444,
    0x21177544, 0x27ab7744, 0x413cba44, 0x624ce744, 0x86b12444, 0xb3142d44, 0xf0ad3244, 0xe0a64144,
    0xb20a5344, 0xad726144, 0x88d36144, 0xa5ef7345, 0x9e117445, 0x2e048e45, 0xfb388e45, 0x7c8f9045,
    0x13cca445, 0xdd95a545, 0x27f8a545, 0xbd92ab45, 0xc3e41145, 0x5757ac45, 0x3f78cb45, 0x8ffff445,
    0xadfdf645, 0x55dcf845, 0x3ca82345, 0x44a43245, 0x565e4645, 0x81405045, 0x02a05745, 0x7e980945,
    0xd87a6446, 0x68847046, 0x1a59b446, 0x99b6bb46, 0x3b46f146, 0xfd5e1b46, 0x45384846, 0x8d3b4946,
    0x0f2d4c46, 0xf96c4d46, 0xfd5b5846, 0xd9c05b46, 0x875a5e46, 0xbc650a47, 0xba197a47, 0xc7230d47,
    0xb4440e47, 0x0b5aae47, 0xe5ffb847, 0x508bc147, 0x9b41c147, 0x95e2c247, 0xfa38c747, 0xc0b2cb47,
    0x88eace47, 0x1988d847, 0xe9692f47, 0x52d23847, 0x7e143b47, 0x587f3f47, 0x2d674f47, 0xf8105347,
    0xa89e5c47, 0x370e5d47, 0x783eac48, 0x5aa6b148, 0x3a52b148, 0x63cdb248, 0x776ab748, 0x6535be48,
    0x1b97bf48, 0x2a21bf48, 0xf0afc848, 0xb42ec848, 0xc42fc848, 0xe23ac848, 0x608dea48, 0xb5cbf148,
    0x24bef348, 0xe41d0948, 0xab1e0948, 0x7d8e684a, 0xde3dc14a, 0x4574c74a, 0x47aad04a, 0xad14264a,
    0xe4d13f4a, 0xbfa3414a, 0xe1384c4a, 0x4cfa6a4b, 0xea77784b, 0x78dc804b, 0x1595854b, 0x82bba14b,
    0x2b37b34b, 0xea84484b, 0x533a534b, 0x5299544b, 0x1d830a4c, 0xe7a20a4c, 0x21ff6e4c, 0x2c4d6e4c,
    0xf44d764c, 0x496d7b4c, 0x23b8024c, 0x3e38164c, 0x9de4184c, 0xcce31b4c, 0x567f1e4c, 0x42e9044c,
    0x60034e4c, 0x8c044f4c, 0xd5585e4c, 0x3eef624c, 0x43f6744d, 0x2b38a84d, 0x500cbe4d, 0x911dbe4d,
    0x3fc7bf4d, 0xa840bf4d, 0x8c4cbf4d, 0x67f2ca4d, 0xfeafef4d, 0xa5b5f74d, 0x62b01b4d, 0x40b21b4d,
    0x77d71b4d, 0xaa161b4d, 0x9854284d, 0x1f852d4d, 0xb2ad2e4d, 0xc300074d, 0x61294d4d, 0x3786664e,
    0x86ea6b4e, 0xc1366c4e, 0xaeb3854e, 0x1d58864e, 0x1af8d34e, 0x2ae0d54e, 0x8996e94e, 0x1bdcf74e,
    0x387e1b4e, 0x26691f4e, 0x3702244e, 0xcd753e4e, 0x2d44084e, 0xace5654f, 0x6190834f, 0x07228b4f,
    0x21a18d4f, 0x14a28d4f, 0x1545994f, 0x1149a74f, 0x671bad4f, 0xca89b54f, 0xecaebf4f, 0x5ad8c74f,
    0x5474cd4f, 0x3f6fe54f, 0x3cdbf14f, 0xe3811f4f, 0x1a4a204f, 0xc888284f, 0xcff44f4f, 0x0efc4f4f,
    0x352f524f, 0x43888a50, 0xeca88a50, 0x2765b150, 0x6b27c150, 0xce62d450, 0xa5cada50, 0x2349dc50,
    0xd559dc50, 0x4ae2ed50, 0x35abee50, 0xa9606851, 0xf7069d51, 0x00d6be51, 0x42debe51, 0xa637c951,
    0xa6adce51, 0x337d1751, 0x5ab11e51, 0x0c910351, 0xb22a3e51, 0x7f3a6151, 0x835a6151, 0x1f060c52,
    0x3e0d8b52, 0xfa278f52, 0x0a10a052, 0xf0d2a152, 0x72c9c552, 0xc51fd352, 0x3aa4d952, 0x91c0e052,
    0x8684e652, 0xdaf41752, 0x17c1ea52, 0x5d1b2452, 0x00722752, 0x6a404552, 0x57159553, 0xc4229553,
    0xe114ac53, 0x13361653, 0x73491753, 0x16751853, 0xbfc51953, 0x5f0cff53, 0x4d221a53, 0x4d962053,
    0x7fd02853, 0xf1582b53, 0xcf2f0553, 0x97b03853, 0x65bb3853, 0xf2f05253, 0xeb4c5353, 0x8bd95453,
    0x32436a54, 0x190d6f54, 0x6fd68754, 0xfbe68754, 0x72ef8754, 0x9fd39754, 0x2577b454, 0xf557e154,
    0xa96afa54, 0x11892b54, 0xd5223054, 0x0acd3a54, 0xbed53a54, 0x8af23a54, 0x6af93a54, 0xab043a54,
    0x33965c54, 0xb6ea0a55, 0x43827655, 0x5ea08b55, 0x1189b055, 0x7b24b755, 0x6390d855, 0x0f96d855,
    0x84b2de55, 0x59c8e455, 0x0311eb55, 0x9373ee55, 0xe452f055, 0x19450455, 0xed598656, 0xadb08856,
    0x42cc8856, 0x3c0f8f56, 0xcdef9156, 0xfc8f9256, 0x07629656, 0x3987a656, 0xc909b356, 0x1765b756,
    0x0e67b756, 0x872a1d56, 0x33d90356, 0x261b2056, 0xa0f02256, 0x842d3d56, 0xba5e3f56, 0x95f24956,
    0x3c7c4a56, 0xa2c36757, 0x99236e57, 0x3c8a7057, 0xda159157, 0x91179157, 0xb0219c57, 0xb8399c57,
    0x2087ac57, 0xce0bb757, 0xf319b757, 0xa964c257, 0xeb68c357, 0xf406dd57, 0xaa57fe57, 0xfefa6257,
    0xf4cf7058, 0x34cf9f58, 0x1963a158, 0xe7b8c658, 0x5b8bc758, 0x2c1ace58, 0xbe23d958, 0xf223d958,
    0x7b33d958, 0x5433d958, 0xe735d958, 0x0938d958, 0x70f51c58, 0xe4e51f58, 0xce304758, 0xdfb56659,
    0x7dd58e59, 0xb56ba259, 0xb777ac59, 0x0674b159, 0x9371bf59, 0xe0fcc859, 0xb387cc59, 0x448bcc59,
    0xf2961759, 0x6f14f759, 0x5f241f59, 0x71ca4059, 0x38ba4459, 0xcdd70759, 0x29a74a59, 0x9c9a4c59,
    0xa275b65a, 0xf1efbc5a, 0xc773d75a, 0x8805155a, 0x0fc5d75a, 0x029bdc5a, 0x6a40f45a, 0x8642f45a,
    0xfb45f45a, 0x5245f45a, 0x7c48f45a, 0x7049f45a, 0x29a9735b, 0xc5ba755b, 0x1e907b5b, 0xebc17e5b,
    0x3127925b, 0x35379a5b, 0xa35a9a5b, 0x2ec6c05b, 0xd633d15b, 0x6839d35b, 0x18d4e25b, 0x7e4ee85b,
    0x41d22a5b, 0x2e0e595b, 0xb113595b, 0x96a05a5b, 0xa5cc095b, 0xa8d8095b, 0xad57645c, 0xa800765c,
    0x194fc95c, 0x9452ea5c, 0xcba9eb5c, 0x05b0ef5c, 0x8fb2f05c, 0x3e50f75c, 0xba94f95c, 0x4ec4fb5c,
    0xb5ceff5c, 0xf5921a5c, 0x25f51b5c, 0x86c1275c, 0x54ff285c, 0x55ff285c, 0x1b964d5c, 0x435f515c,
    0x48587e5d, 0xcf60855d, 0x8095865d, 0xd0a0865d, 0xbba2865d, 0x0aa7865d, 0xed9b985d, 0x7939ac5d,
    0x66d0b45d, 0x6fa9b55d, 0x1274ca5d, 0xf67cca5d, 0x2b41d45d, 0x36e6235d, 0x0bec275d, 0x7202495d,
    0xa6004b5d, 0xbb184f5d, 0x11aa515d, 0x6734515d, 0x0924565d, 0x7c6f575d, 0xa1a2575d, 0x6ba3575d,
    0x5cb0575d, 0xf2ec575d, 0x4684605d, 0x06a0615d, 0xd6fe0a5e, 0xa741715e, 0x1ee88f5e, 0x9797aa5e,
    0x2fe4aa5e, 0x0d16ac5e, 0x49d3ae5e, 0x055eae5e, 0x3317af5e, 0x8d0bb35e, 0x2980b35e, 0x1d2fb35e,
    0x3437bc5e, 0x3ae0c05e, 0x60d1c35e, 0xc0c9d05e, 0x4a04dc5e, 0x2913e35e, 0xf5e4e55e, 0x101ce65e,
    0x1ae4195e, 0x56e4195e, 0x92bdfd5e, 0xf13f435e, 0x3be3455e, 0x33ea455e, 0x78fb495e, 0x4011085e,
    0xa10f695f, 0x8a9c6e5f, 0xcfa0855f, 0xebca855f, 0x46238d5f, 0xc69b105f, 0x1d09105f, 0xcb26ae5f,
    0xd69b125f, 0x1ff2125f, 0xda26d35f, 0x7ccedd5f, 0x5aedf35f, 0x03e81b5f, 0xe7c4205f, 0x7de1215f,
    0x99e1275f, 0xdf662a5f, 0x55f8395f, 0x0a033d5f, 0xf9db425f, 0x8efa5b5f, 0x08131560, 0xf64d1760,
    0xe78ef260, 0xf370f860, 0x1d36fd60, 0xfb822b60, 0xaa8f2c60, 0xed633060, 0xe2a84b61, 0x027d5161
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0xba;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0x56;
        vAlertPubKey = ParseHex("04fc9702847840aaf195de8442ebecedf5b095cdbb9bc716bda9110971b28a49e0ead8564ff0db22209e0374782c093bb899692d524e9d6a6956e7c5ecbcd68284");
        nDefaultPort = 13333;
        nRPCPort = 13332;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 32);
        nSubsidyHalvingInterval = 1050000;
        nTargetTimespan = 60 * 60;
        nTargetSpacing = 2 * 60;
        nInterval = nTargetTimespan / nTargetSpacing;

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
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
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
            const int64 nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0xba;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0x56;
        vAlertPubKey = ParseHex("0415e63deb4a13fc9aa182121fd8b3cc582c205f57dabdf291b71e2c298060cec4f06bc3806485f45f19d07e48c1e1874fbab82ad7b8420866914ee00aeac75291");
        nDefaultPort = 23333;
        nRPCPort = 23332;
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
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 24444;
        strDataDir = "regtest";

        /* genesis block generation */
        /* FIXME generate that one too
        uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        //printf("bnProofOfWorkLimit=%s\n", bnProofOfWorkLimit.ToString().c_str());
        //printf("        hashTarget=%s\n", hashTarget.ToString().c_str());
        //printf("        block hash=%s\n", genesis.GetHash().ToString().c_str());
        while (genesis.GetHash() > hashTarget)
        {
            ++genesis.nNonce;
            if (genesis.nNonce % 1000000 == 0) {
                //printf("current regtest tested nNonce=%u\n  hash=%s\ntarget=%s\n", genesis.nNonce, genesis.GetHash().ToString().c_str(), hashTarget.ToString().c_str());
            }
            if (genesis.nNonce == 0)
            {
                //printf("NONCE WRAPPED, incrementing time");
                ++genesis.nTime;
            }
        }
        //printf("regtest genesis hash=%s nNonce=%u nTime=%u\n", genesis.GetHash().ToString().c_str(), genesis.nNonce, genesis.nTime);
        //printf("regtest merkle root=%s", genesis.hashMerkleRoot.ToString().c_str());
        */
        /* END genesis block generation */

        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")); // FIXME re-enable this

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
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

