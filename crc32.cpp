#include "crc32.h"
#include "boost/crc.hpp"
#include "boost/lexical_cast.hpp"
#include <string>

std::string crc32(const std::string& my_string) {
    boost::crc_32_type result;
    result.process_bytes(my_string.data(), my_string.length());
    return boost::lexical_cast<std::string>(result.checksum());
}