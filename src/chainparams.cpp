// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
/*
#include <stdio.h>
#include "hash.h"
#include "scrypt.h"
#define SCRYPT_BUFFER_LEN (131072 + 63)
bool static ScanHash(CBlock* pblock, uint256& thash)
{
    unsigned char scratchpad[SCRYPT_BUFFER_LEN] = {0x00};
    uint256 hashTarget = CBigNum().SetCompact(pblock->nBits).getuint256();
    while(true)
    {
        pblock->nNonce +=1;
        thash = scrypt_blockhash(CVOIDBEGIN(pblock->nVersion));
        if(thash <= hashTarget)
            break;
    }
    return true;
}
*/
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf8;
        pchMessageStart[1] = 0xe9;
        pchMessageStart[2] = 0xe1;
        pchMessageStart[3] = 0xef;
        vAlertPubKey = ParseHex("0423f3c25f36764f79f7ec50109e59339c5f39e0d1e79944fd4d0f7eb3706c29fe935bb5e3f5ecfca4982bf1c6ceb798286b9b41f170850e49c8831efc31b2b6e6");
        nDefaultPort = 19771;
        nRPCPort = 19772;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 17);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "FidChain";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1499097600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1499097600;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 25392;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00001312cef9daf03d3ddeecaa0d8995c72595366af4850353082ca88ac584a9"));
        assert(genesis.hashMerkleRoot == uint256("0x2569ace545f41a07034e1fb402d8e3a0f3b4c66b2bc418585d09dd1cdd0943bd"));

        vSeeds.push_back(CDNSSeedData("120.55.61.133", "120.55.61.133"));
        vSeeds.push_back(CDNSSeedData("47.92.98.238", "47.92.98.238"));
        vSeeds.push_back(CDNSSeedData("39.108.173.85", "39.108.173.85"));
        vSeeds.push_back(CDNSSeedData("39.108.154.111", "39.108.154.111"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(36);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(95);
        base58Prefixes[SECRET_KEY] =     list_of(250);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 4000;
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
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xed;
        pchMessageStart[1] = 0xe5;
        pchMessageStart[2] = 0xee;
        pchMessageStart[3] = 0xe7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 12);
        vAlertPubKey = ParseHex("04dd6fe71bd7ab030b6482c649e41d0587f68fba79acc8a78dcf53f19e2e7ad7a330b2f65ad197c578ae1f8a85a5208506bb794e7c9970088a97dc99c3b3bfa560");
        nDefaultPort = 29771;
        nRPCPort = 29772;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 4397;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00057a7a879138f4729067e82c57efcb0d64cad14fadbcc01e6881030387aaf6"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(36);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(95);
        base58Prefixes[SECRET_KEY]     = list_of(250);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0xffffffff;
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
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xb0;
        pchMessageStart[2] = 0xb1;
        pchMessageStart[3] = 0xb6;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 39771;
        nRPCPort = 39772;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x19c918805a6334baca2de15587647268fd8e9a062d17ac6d435044ccb7b3521e"));

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
