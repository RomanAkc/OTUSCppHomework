#include <iostream>
#include <string>

#include "CommandLineParser.h"

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

    //TODO: check params (directories, level, wildcards, hash algorithm)

    //TODO: compare

    //TODO: print result

    /*auto vecDir= vm["dir"].as<std::vector<std::string>>();
    for(auto& dir : vecDir) {
        std::cout << dir << std::endl;
    }

    if(vm["level"].as<int>() == 1 || vm["level"].as<int>() == 0) {
        std::cout << "level = " << vm["level"].as<int>() << std::endl;
    }
    else {
        std::cout << "Bad command line. Use --help for more information" << std::endl;
    }*/

	std::cout << "Hello, world!" << std::endl;
	return 0;
}
