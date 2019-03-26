// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "crypto/equihash.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "base58.h"

using namespace std;

#include "chainparamsseeds.h"

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strCurrencyUnits = "SGHX";
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 2;
        consensus.nSubsidyHalvingInterval = 1400000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 13;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 34;
        consensus.nPowMaxAdjustUp = 34;
        consensus.nPowTargetSpacing = 1.5 * 60;
        /**
         * The message start string should be awesome! ⓩ❤
         */
        pchMessageStart[0] = 0x2a;
        pchMessageStart[1] = 0xe7;
        pchMessageStart[2] = 0x26;
        pchMessageStart[3] = 0x63;
        vAlertPubKey = ParseHex("04d5212ed0303c64db1840e799d31953eb362fd71d8e742dccd9aa78c4713d6d26b44974b44e2ac71aa38b06ef60c020207b85d270e4bdf8c797f3216f969960dc");
        nDefaultPort = 7002;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 0xFFFFFFFF;
        newTimeRule = 159300;
        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh200_9;
        eh_epoch_1_endblock = 0xFFFFFFFF;
        eh_epoch_2_startblock = 0xFFFFFFFF;

        /**
         * Build the genesis block. Note that the output of its generation
         * transaction cannot be spent since it did not originally exist in the
         * database (and is in any case of zero value).
         *
         * >>> from pyblake2 import blake2s
         * >>> 'BitcoinZ' + blake2s(b'BitcoinZ - Your Financial Freedom. Dedicated to The Purest Son of Liberty - Thaddeus Kosciuszko. BTC #484410 - 0000000000000000000c6a5f221ebeb77437cbab649d990facd0e42a24ee6231').hexdigest()
         */
        const char* pszTimestamp = "Supremecoin";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.SetNull();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
        genesis.nTime    = 1551701289;
        genesis.nBits    = 0x1f07ffff;
        
        genesis.nNonce   = uint256S("0x0000000000000000000000000000000000000000000000000000000000001e54");
        genesis.nSolution = ParseHex("004a24b2cb8e0dded35782a9221bb1073b1b7f55d014e057f0d6d8ccbadc794618b3fbbec9bc4976539c0fcb91c1d4e753e3fa2fc340c6308fca9ca4deec966036f50b4f7aa62dfbe9589fbd5e1b3a656d5ee5fc1859c78821af77efe0b8e29faf727e6266ce57f3dd1abdd3da26873114485c55ef8bf74181c4f7fbd9de186bc7298bcd510123f685589fdef75e4ea05a09301ed7a417c9e104e16c6384f286f04b1e87d818aa190050f4508878737dd1083154466e6a34804d7118a30cd64ec335690e0fe574e12d6466a9bdd30bbce237023037bf17ce15d5a622764d0bc7d2fac6baf8ca7507bb037f9c10d26cd9e6937710e86ff6a13d78aeac04ba47cb27e822b9eb9340b88fa38db4f1321ae3266e90db75a2a5ef63e3c58ae544e2613eeea39ff9f20cac1ddfb54b47255c247878b0602cdb0a161fba471528077009189574f56f35dc2978c79245a1b7b0d201951a7a168664751e06732508a6d746fc9fde90e6106a023907c9d755611b115212bd6451caaa5f886e0452654f9e882989491852a4491ecbf932ba10b70f3b0c830f8117209bf05e84e91f7bffb2cf5f7e7df90533efbb11d142cf7ec0c2c69d22d69e26d55e684d13c4b8a951088df7aad6843d56be8da12946bc5c65062c6bb4c1ad71b5d4d8912e80504538f7b2ef6e951628df371acbb7ff9e7929cb5f508652bc295c72d204637705fd197cf170e95132fbb5c8ad8b7239206967de1cdf7ea4caf5860dc7031f6eb7cacddf3f8ef104c9d3b6cf930e393ba4e18fa85232717cf7bdf5c14e79ab7fed727ea7abf898b59d7f2d97b1b41fa551071b2e0c5585360c5f4665b3ead5db6dbf00ba7a6534a2bb5220bbd195f17e03a3ec7c264da8225f09a20f6a868f84d2efdea4678141f96af5e0e0826f4cee356d94a419e6fd1d5d33c4a9326dba5afc595c744c01f6c556485f3ba322352657c645c2f7bc9f9e9bf310539fd9d7d1cf7715ac01a936fe40a92afef2e9931e91ff66b80e4501552ae2924f7e018cbdbadada406e96d552bb38d0ebd3d86b12a5f78b52e4a01ad1461601236a079f7e93083b63253df689dda893f16b984b883c0d4ce310958ccb383e305eb1dad4023ce62f199602c2ee4b74ec5bb4a1a854dbc070e9f94c1694496b04f8491d3f174e070bf5bee05f2fae09de440d065338972e5d8e4971bc317b5210863a74159d5475066826d0cef123f9fa9ce38a849dc48a18d49ff20413c657663493c60b9ecab2184e39e99ab700bf44da1de57413f036c887ff85e421ce2e547134eb31836a09bd9d2062a482ef477c633877b001d6ec1738fd410dd45cac49d32c4afbbf75b546c65096280c3d069f0f408cfaf0b65889b62d03dd8f31dc7f8bf65da3795a664cc18ca816eb4d9885e4403f448a2548b2877901fe18ea9905ab71ccc2d20bd6cba1e368abfc46321c2e49f34e1d5a39f6f50464097947a53e2816a08d18f43f94e0f2dd81ec85953d156ffbd697ec578ebf1e7825f80b2a8689550a422a29f1f7cd9e95b8e5230a2636d190ca9d0786f96551f22ac67a55241f6cef0ef90998d22eb15dffed632feef713d76c8b5ea0b930a74c308c1479d745aa17b07a432056ac66dab6e4326cf3bbe129fbfd70c4345e89a4987f56dcfe8c5e03c938551ccd0f791100230335dd2a82b2be3bd390058151a35e97d40f6f2fc3a48244107e1349d639fa06250c52174a636f794a41f7e61aa821dd597e3ad31376fb7a4e158b0ebecb83fdcd5a3a7d0bf25ddcdd07bde59d581ae9fb1f84c17291fd0e322e52d53bdd1fc7eebe935beef5c63f51fca4ed18d9aaf83e2b130a453ea0089a1467aaeb149032cc6c538433bf0b8d0ac1ffde4d4bd9594b7f1192d352b4a9926aaff6d7");

        consensus.hashGenesisBlock = genesis.GetHash();
 	    printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%s\n", genesis.nNonce.ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x143eb2848fd29e19e76a5ab56f49a8f5e3e7c02372b8ec2e9e849c3b0b583b87")); //incremented by 1 making 2
        assert(genesis.hashMerkleRoot == uint256S("0x9f1f8d7b6bb85df75ff5613db1c37fda7b9b594b2f385e43a43eee2c51dad9db"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // use name as: echo -n hostname | sha256sum
        


        // guarantees the first 2 characters, when base58 encoded, are "t1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1C,0xB8};
        // guarantees the first 2 characters, when base58 encoded, are "t3"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBD};
        // the first character, when base58 encoded, is "5" or "K" or "L" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0x80};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x88,0xB2,0x1E};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x88,0xAD,0xE4};
        // guarantees the first 2 characters, when base58 encoded, are "zc"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0x9A};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVK"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAB,0xD3};
        // guarantees the first 2 characters, when base58 encoded, are "SK"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAB,0x36};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x0006baa3ba4091d3c0014e96bf3edd55f733d7e1f5dea75f6a29ae19af75d7b0")),

            1530166456,     // * UNIX timestamp of last checkpoint block
            662217,         // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            2290.912865  // * estimated number of transactions per day after checkpoint
                            //   total number of tx / (checkpoint block height / (24 * 24))
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
        };
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "testnet";
        strCurrencyUnits = "SGHX";
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 2;
        consensus.nSubsidyHalvingInterval = 1400000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 13;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 34;
        consensus.nPowMaxAdjustUp = 34;
        consensus.nPowTargetSpacing = 1.5 * 60;
        /**
         * The message start string should be awesome!
         */
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0x1b;
        pchMessageStart[2] = 0xf8;
        pchMessageStart[3] = 0xbc;
        vAlertPubKey = ParseHex("86437ztLB968376APc4LS7Dhn5s6X78K9SvcV4XNnFSN7PedxKsDccA3oM59yby1NycHrS6D7E9iAPq12z4An6NUK300653291803cGsKU7a2wqzScQkttRRjB4aHbHbsQ");
        nDefaultPort = 17002;

        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 0xFFFFFFFF;
        newTimeRule = 159300;
        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh200_9;
        eh_epoch_1_endblock = 0xFFFFFFFF;
        eh_epoch_2_startblock = 0xFFFFFFFF;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1551113712;
        genesis.nBits = 0x2007ffff;
        genesis.nNonce = uint256S("000000000000000000000000000000000000000000000000000000000000000a");
        genesis.nSolution = ParseHex("010d91a2a6a68425ff2d61934bad2e39b001ba41fb0cee59130091bb4891455384c69c89457f90d8669d2b7ce98c9b5d0bc77a0524eac46c8b671a24bfe2ab2d87b300fb73b32bfe3df3f6a4f7e089a9ad36b31615dadc8c16e49d6d65b53440f8297c715a8ef10ff31da3db45b3d688e32ea506183a6821ffcf9edfa1f7199582cc7e958dc564c437e121feff8e5034156a403d3b2f605076e30bf640d4791046d9cebd8c1ac7c607784cdc735b640de73230ab2725f11a318e5e4edb1831516b53576d7913ee524b051f7dbcc8e3b57b64308ecf81020cc0bb2b5e455b03ef6d2171ce8c38533ba36c970da1ce2f442a54dd74f288c5d30814c02f11c28bbef5a0b6b9e0b972989b3275cae88fb94b72135458bfcd47de16d59081531ef3c5910d1caf44be1a5425eddc5477ebd03f85b331b69889e98b9bba2027ce22d606ccd59f9468b2849e15be7d11dbd1d35d053e67b4443016b5a93350acabaa60e6614e19f2b622a1af42c94eec097af2c4e93e68ea31b8780e71070a86f796964730c0803c028c349509fea1499d4a53576e1eb65726a0634666b5ad8979b037333cdf0bbc0efc931a6c64fffbe598824763d53b594a83f0a4714498eba3282e599dee6be45bfc467682b810d83c46213bc5082a974280e9ede7ac41fcd8a261c11c45ec5fab6f58e5ada7a1cefd86cdf2c22a1a6c4ef754db07ded5629b0ba03df08c865e38c06b45e7655cf61c13e4ea3fe7ca84776442a14ecc3b37e45a4397992e13bd28d35731e643d1cff22064a29889fd0b3709cc69cf0e3279dbf7dd7a43784beaf58e07196c3cba4916f9325f8f5631dab64535bfc366bb9e4f50f28532261c9d42861ee5ff9ddf48124fcc94f6d220d86d77197172f741e1c72b3c9002befe3a418acb987fb6cf1b6b36a6c4fa1507f42f5415392ef6ff25e4bd08d703631ca5881af0ff9a860100af38607ade397c401511942fc15b8afe36635a93966f249da9ba61509920065d06684983a2b691dc60ffc0232f4c910872ffa40c0ded493892841b679a047935cc6df2c040f6479405c5f3bfd644fa27908ae418b0a9b13506e8fd7f7a07334995c75177830cc33603dc5db69e765f345f6d318c94cc348c9137ea9a2501bf423eb9c3758edfe435278f0c42e3567737e8b506346d5d872e1f9e72470b627ffdae8fe2b13ee5f5c675dc38d9bd1f16dc2a54d36441b05d716f4de878b1da6389629152787e361dda74ee5a2ae5118e5c7857c24f642221e8ddb882431a152a40de470b8e4b07f910d184f27674de5169186434ad78e3900d7b14356321c0fa86bcc7dc427c1afc9ec98ddad443beb5e37776e51c7151de18f7632ee605b55f1cb8459fcdf56918d2f3d97c014cfdbe8ac656d546261059b9a2496f5a696da398fa1dbbe603edf5e460d20af9418544c6fb2c831d7cab923d5e4f4aab2c86b1008bdedde8bc184da82a586df52ae424a80b7cae2cbf237f89f90b99c9208355cedf6fa92fa8275e8b0d35f7ff29f4594473fb4d425e6f495d06843282c84d15ccbb87d153a9914b523ed91f4095087960cee6c762e8b61f73ff2a5597edb595fbe9a119cb818bc74ebf889ac356a42fd7261a5dbf1b82232f0047bed2e44649d5962589c8f835b9728efa5c27072c3da7901d65d9b99cd9a102ea506377175ebfde0a4615225c0e72f0fdafd8d36aff970ba8dc9e81d10e565edee0aa470fe3f132e7f4fc71bd644512130058b18e864fbba835ec37162b55b86e9a3b4876acde0b96692df50def53591cd25c7bf6022cec5b59bac464500d530027912fb1484742d5bc86da10a07cba0827717f7d695d6c11fe31a827267f6daecf313aaf67719cde852eab8cffbcbcba0cef5372fb4b005c9334");

        consensus.hashGenesisBlock = genesis.GetHash();
        printf("Testnet genesis: %s\n", consensus.hashGenesisBlock.ToString().c_str());
        printf("Testnet merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%s\n", genesis.nNonce.ToString().c_str());

        assert(consensus.hashGenesisBlock == uint256S("0x04c5c0303ba859ee465be9b34cea34f883d76ce803ad522469290f31c031faab")); //incremented by 1 making 2
        assert(genesis.hashMerkleRoot == uint256S("0x9f1f8d7b6bb85df75ff5613db1c37fda7b9b594b2f385e43a43eee2c51dad9db"));
        vFixedSeeds.clear();
        vSeeds.clear();
      //  vSeeds.push_back(CDNSSeedData("978b674532d58328c4da63ab138c476ffa2f8a8b2b5a023a668fd3a97eb7c48b.TZB", "testnetseed.btcz.biz"));
        //vSeeds.push_back(CDNSSeedData("rotorproject.org", "test-dnsseed.rotorproject.org")); // Zclassic

        // guarantees the first 2 characters, when base58 encoded, are "tm"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1D,0x25};
        // guarantees the first 2 characters, when base58 encoded, are "t2"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBA};
        // the first character, when base58 encoded, is "9" or "c" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        // guarantees the first 2 characters, when base58 encoded, are "zt"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVt"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        // guarantees the first 2 characters, when base58 encoded, are "ST"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x04c5c0303ba859ee465be9b34cea34f883d76ce803ad522469290f31c031faab")),
            1320156356,     // * UNIX timestamp of last checkpoint block
            342516,         // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            3490.8463  // * estimated number of transactions per day after checkpoint
                            //   total number of tx / (checkpoint block height / (24 * 24))
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
        };
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strCurrencyUnits = "REG";
        consensus.fCoinbaseMustBeProtected = false;
        consensus.nSubsidySlowStartInterval = 0;
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 0; // Turn off adjustment down
        consensus.nPowMaxAdjustUp = 0; // Turn off adjustment up
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xe4;
        pchMessageStart[2] = 0x3a;
        pchMessageStart[3] = 0x5b;
        nMaxTipAge = 24 * 60 * 60;

        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh200_9;
        eh_epoch_1_endblock = 0xFFFFFFFF;
        eh_epoch_2_startblock = 0xFFFFFFFF;

        genesis.nTime = 1551113712;
        genesis.nBits = 0x2007ffff;
        genesis.nNonce = uint256S("000000000000000000000000000000000000000000000000000000000000000a");
        genesis.nSolution = ParseHex("010d91a2a6a68425ff2d61934bad2e39b001ba41fb0cee59130091bb4891455384c69c89457f90d8669d2b7ce98c9b5d0bc77a0524eac46c8b671a24bfe2ab2d87b300fb73b32bfe3df3f6a4f7e089a9ad36b31615dadc8c16e49d6d65b53440f8297c715a8ef10ff31da3db45b3d688e32ea506183a6821ffcf9edfa1f7199582cc7e958dc564c437e121feff8e5034156a403d3b2f605076e30bf640d4791046d9cebd8c1ac7c607784cdc735b640de73230ab2725f11a318e5e4edb1831516b53576d7913ee524b051f7dbcc8e3b57b64308ecf81020cc0bb2b5e455b03ef6d2171ce8c38533ba36c970da1ce2f442a54dd74f288c5d30814c02f11c28bbef5a0b6b9e0b972989b3275cae88fb94b72135458bfcd47de16d59081531ef3c5910d1caf44be1a5425eddc5477ebd03f85b331b69889e98b9bba2027ce22d606ccd59f9468b2849e15be7d11dbd1d35d053e67b4443016b5a93350acabaa60e6614e19f2b622a1af42c94eec097af2c4e93e68ea31b8780e71070a86f796964730c0803c028c349509fea1499d4a53576e1eb65726a0634666b5ad8979b037333cdf0bbc0efc931a6c64fffbe598824763d53b594a83f0a4714498eba3282e599dee6be45bfc467682b810d83c46213bc5082a974280e9ede7ac41fcd8a261c11c45ec5fab6f58e5ada7a1cefd86cdf2c22a1a6c4ef754db07ded5629b0ba03df08c865e38c06b45e7655cf61c13e4ea3fe7ca84776442a14ecc3b37e45a4397992e13bd28d35731e643d1cff22064a29889fd0b3709cc69cf0e3279dbf7dd7a43784beaf58e07196c3cba4916f9325f8f5631dab64535bfc366bb9e4f50f28532261c9d42861ee5ff9ddf48124fcc94f6d220d86d77197172f741e1c72b3c9002befe3a418acb987fb6cf1b6b36a6c4fa1507f42f5415392ef6ff25e4bd08d703631ca5881af0ff9a860100af38607ade397c401511942fc15b8afe36635a93966f249da9ba61509920065d06684983a2b691dc60ffc0232f4c910872ffa40c0ded493892841b679a047935cc6df2c040f6479405c5f3bfd644fa27908ae418b0a9b13506e8fd7f7a07334995c75177830cc33603dc5db69e765f345f6d318c94cc348c9137ea9a2501bf423eb9c3758edfe435278f0c42e3567737e8b506346d5d872e1f9e72470b627ffdae8fe2b13ee5f5c675dc38d9bd1f16dc2a54d36441b05d716f4de878b1da6389629152787e361dda74ee5a2ae5118e5c7857c24f642221e8ddb882431a152a40de470b8e4b07f910d184f27674de5169186434ad78e3900d7b14356321c0fa86bcc7dc427c1afc9ec98ddad443beb5e37776e51c7151de18f7632ee605b55f1cb8459fcdf56918d2f3d97c014cfdbe8ac656d546261059b9a2496f5a696da398fa1dbbe603edf5e460d20af9418544c6fb2c831d7cab923d5e4f4aab2c86b1008bdedde8bc184da82a586df52ae424a80b7cae2cbf237f89f90b99c9208355cedf6fa92fa8275e8b0d35f7ff29f4594473fb4d425e6f495d06843282c84d15ccbb87d153a9914b523ed91f4095087960cee6c762e8b61f73ff2a5597edb595fbe9a119cb818bc74ebf889ac356a42fd7261a5dbf1b82232f0047bed2e44649d5962589c8f835b9728efa5c27072c3da7901d65d9b99cd9a102ea506377175ebfde0a4615225c0e72f0fdafd8d36aff970ba8dc9e81d10e565edee0aa470fe3f132e7f4fc71bd644512130058b18e864fbba835ec37162b55b86e9a3b4876acde0b96692df50def53591cd25c7bf6022cec5b59bac464500d530027912fb1484742d5bc86da10a07cba0827717f7d695d6c11fe31a827267f6daecf313aaf67719cde852eab8cffbcbcba0cef5372fb4b005c9334");
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 27002;
        assert(consensus.hashGenesisBlock == uint256S("0x04c5c0303ba859ee465be9b34cea34f883d76ce803ad522469290f31c031faab"));
        nPruneAfterHeight = 0xFFFFFFFF;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x04c5c0303ba859ee465be9b34cea34f883d76ce803ad522469290f31c031faab")),
            0,
            0,
            0
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        //vFoundersRewardAddress = { "t2FwcEhFdNXuFMv1tcYwaBJtYVtMj8b1uTg" };
    vFoundersRewardAddress = { };
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);

    // Some python qa rpc tests need to enforce the coinbase consensus rule
    if (network == CBaseChainParams::REGTEST && mapArgs.count("-regtestprotectcoinbase")) {
        regTestParams.SetRegTestCoinbaseMustBeProtected();
    }
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}


// Block height must be >0 and <=last founders reward block height
// Index variable i ranges from 0 - (vFoundersRewardAddress.size()-1)
std::string CChainParams::GetFoundersRewardAddressAtHeight(int nHeight) const {
    int maxHeight = consensus.GetLastFoundersRewardBlockHeight();
    assert(nHeight > 0 && nHeight <= maxHeight);

    size_t addressChangeInterval = (maxHeight + vFoundersRewardAddress.size()) / vFoundersRewardAddress.size();
    size_t i = nHeight / addressChangeInterval;
    return vFoundersRewardAddress[i];
}

// Block height must be >0 and <=last founders reward block height
// The founders reward address is expected to be a multisig (P2SH) address
CScript CChainParams::GetFoundersRewardScriptAtHeight(int nHeight) const {
    assert(nHeight > 0 && nHeight <= consensus.GetLastFoundersRewardBlockHeight());

    CBitcoinAddress address(GetFoundersRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    assert(address.IsScript());
    CScriptID scriptID = get<CScriptID>(address.Get()); // Get() returns a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script;
}

std::string CChainParams::GetFoundersRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vFoundersRewardAddress.size());
    return vFoundersRewardAddress[i];
}


int validEHparameterList(EHparameters *ehparams, unsigned long blockheight, const CChainParams& params){
    //if in overlap period, there will be two valid solutions, else 1.
    //The upcoming version of EH is preferred so will always be first element
    //returns number of elements in list
    if(blockheight>=params.eh_epoch_2_start() && blockheight>params.eh_epoch_1_end()){
        ehparams[0]=params.eh_epoch_2_params();
        return 1;
    }
    if(blockheight<params.eh_epoch_2_start()){
        ehparams[0]=params.eh_epoch_1_params();
        return 1;
    }
    ehparams[0]=params.eh_epoch_2_params();
    ehparams[1]=params.eh_epoch_1_params();
    return 2;
}
