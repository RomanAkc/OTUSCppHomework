#include <iostream>
#include <vector>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char ** argv) {
    po::options_description desc("Options");

    desc.add_options()
            ("help,h", "This help")
            ("dir,d", po::value<std::vector<std::string>>()->required()->multitoken(), "Directories for scanning")
            ("level,l", po::value<int>()->default_value(0), "Scan level: 0 (default) - only current directory, 1 - with subdirectories");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if(vm.contains("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    try {
        po::notify(vm);
    } catch (...) {
        std::cout << "Bad command line. Use --help for more information" << std::endl;
        return 0;
    }

    auto vecDir= vm["dir"].as<std::vector<std::string>>();
    for(auto& dir : vecDir) {
        std::cout << dir << std::endl;
    }

    if(vm["level"].as<int>() == 1 || vm["level"].as<int>() == 0) {
        std::cout << "level = " << vm["level"].as<int>() << std::endl;
    }
    else {
        std::cout << "Bad command line. Use --help for more information" << std::endl;
    }

	//std::cout << "Hello, world!" << std::endl;
	return 0;
}
