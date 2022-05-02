#include <string>
#include "crc32.h"
#include "md5.h"
#include "HashAlgorithm.h"

IHashAlgorithm::~IHashAlgorithm() {}

std::string CRC32HashAlgorithm::calcHash(const std::string &s) {
    return crc32(s);
}

std::string MD5HashAlgorithm::calcHash(const std::string &s) {
    return md5(s);
}


