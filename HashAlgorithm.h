#pragma once
#include <string>

class IHashAlgorithm {
public:
    virtual ~IHashAlgorithm();
    virtual std::string calcHash(const std::string&) = 0;
};

class CRC32HashAlgorithm : public IHashAlgorithm {
public:
    std::string calcHash(const std::string &string) override;
};

class MD5HashAlgorithm : public IHashAlgorithm {
public:
    std::string calcHash(const std::string &string) override;
};
