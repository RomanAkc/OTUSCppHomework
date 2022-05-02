#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include "CommandLineParser.h"
#include "FilesComparator.h"
#include "HashAlgorithm.h"


std::shared_ptr<IHashAlgorithm> makeHashAlgorithm(const std::string& name);

int main(int argc, char ** argv) {
    CommandLineParser parser;
    auto parseResult = parser.parse(argc, argv);

    if(parseResult.result == Result::R_SHOWHELP) {
        std::cout << parser << std::endl;
        return 0;
    } else if (parseResult.result == Result::R_BADCOMMAND) {
        std::cout << parseResult.error << std::endl;
        std::cout << "Bad command line. Use '--help' for more information" << std::endl;
        return 0;
    }

    auto params = parser.getParseParams();

    //TODO: check params (directories, level, wildcards) ???
    //TODO: use exclude dir
    //TODO: use wildcards
    //TODO: use hash algo
    //TODO: add exceptions
    //TODO: fix code

    auto hashAlgorithm = makeHashAlgorithm(params.algorithm);

    FilesComparator fc(params, hashAlgorithm);

    auto vecResult = fc.run();

    for(auto& equalFiles : vecResult) {
        for(auto& file : equalFiles) {
            std::cout << file << std::endl;
        }
        std::cout << std::endl;
    }

	return 0;
}

std::shared_ptr<IHashAlgorithm> makeHashAlgorithm(const std::string& name) {
    if(boost::iequals(name, "crc32")) {
        return std::shared_ptr<IHashAlgorithm>(new CRC32HashAlgorithm());
    } else if(boost::iequals(name, "md5")) {
        return std::shared_ptr<IHashAlgorithm>(new MD5HashAlgorithm());
    }
    return nullptr;
}
