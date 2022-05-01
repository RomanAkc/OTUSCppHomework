#include <iostream>
#include <string>
#include "CommandLineParser.h"
#include "FilesComparator.h"

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

    FilesComparator fc(params);



    //TODO: check params (directories, level, wildcards, hash algorithm)

    auto vecResult = fc.run();

    for(auto& equalFiles : vecResult) {
        for(auto& file : equalFiles) {
            std::cout << file << std::endl;
        }
        std::cout << std::endl;
    }

	return 0;
}
