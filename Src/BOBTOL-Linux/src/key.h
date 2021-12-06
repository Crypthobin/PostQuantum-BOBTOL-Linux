#ifndef BITCOIN_KEY_H
#define BITCOIN_KEY_H

#include <pubkey.h>
#include <serialize.h>
#include <support/allocators/secure.h>
#include <uint256.h>

#include <stdexcept>
#include <vector>
#pragma once

typedef std::vector<unsigned char, secure_allocator<unsigned char>> CPrivKey;


bool Dilithium_InitSanityCheck();

#endif // BITCOIN_KEY_H

class CBOBKey
{
public:
    static const unsigned int SIZE = 32;
    static const unsigned int SECRET_KEY_SIZE = 2544;

private:
    bool fValid;

    std::vector<unsigned char, secure_allocator<unsigned char>> keydata;

    unsigned char seckey[SECRET_KEY_SIZE];

    bool static Check(const unsigned char* vch);

    bool Negate();

    bool fCompressed = false;

public:

    CBOBKey() : fValid(false)
    {
        keydata.resize(32);
    }

    friend bool operator==(const CBOBKey& a, const CBOBKey& b)
    {
        return
            a.size() == b.size() &&
            memcmp(a.keydata.data(), b.keydata.data(), a.size()) == 0;
    }

    template <typename T>
    void Set(const T pbegin, const T pend, bool fCompressedIn)
    {
        if (size_t(pend - pbegin) != keydata.size()) {
            fValid = false;
        } else if (Check(&pbegin[0])) {
            memcpy(keydata.data(), (unsigned char*)&pbegin[0], keydata.size());
            fValid = true;
        } else {
            fValid = false;
        }
    }

    unsigned int size() const { return (fValid ? keydata.size() : 0); }
    const unsigned char* begin() const { return keydata.data(); }
    const unsigned char* end() const { return keydata.data() + size(); }

    bool IsValid() const { return fValid; }

    bool IsCompressed() const { return 1;}

    void MakeNewKey();

    CPrivKey GetPrivKey() const;

    CBOBPubKey GetPubKey() const;

    bool Sign(const uint512& hash, std::vector<unsigned char>& vchSig, bool grind = true, uint32_t test_case = 0) const;

    bool Derive(CBOBKey& keyChild, ChainCode& ccChild, unsigned int nChild, const ChainCode& cc) const;

    bool VerifyPubKey(const CBOBPubKey& vchPubKey) const;

    bool Load(CPrivKey& privkey, CBOBPubKey& vchPubKey, bool fSkipCheck);
};

struct CExtBOBKey {
    unsigned char nDepth;
    unsigned char vchFingerprint[4];
    unsigned int nChild;
    ChainCode chaincode;
    CBOBKey key;

    friend bool operator==(const CExtBOBKey& a, const CExtBOBKey& b)
    {
        return a.nDepth == b.nDepth &&
               memcmp(a.vchFingerprint, b.vchFingerprint, sizeof(vchFingerprint)) == 0 &&
               a.nChild == b.nChild &&
               a.chaincode == b.chaincode &&
               a.key == b.key;
    }

    void Encode(unsigned char code[BIP32_EXTPQKEY_SIZE]) const;
    void Decode(const unsigned char code[BIP32_EXTPQKEY_SIZE]);
    bool Derive(CExtBOBKey& out, unsigned int nChild) const;
    CExtBOBPubKey Neuter() const;
    void SetSeed(const unsigned char* seed, unsigned int nSeedLen);
};
