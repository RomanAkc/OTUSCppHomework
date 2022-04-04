#include <iostream>
#include <string>
#include "CommandLineParser.h"
#include "md5.h"

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

    std::cout << md5("hello") << std::endl;

    //TODO: check params (directories, level, wildcards, hash algorithm)

    //TODO: compare

    //TODO: print result

	std::cout << "Hello, world!" << std::endl;
	return 0;
}
