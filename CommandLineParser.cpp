#include "CommandLineParser.h"

using VecStr = std::vector<std::string>;

CommandLineParser::CommandLineParser() {
    std::vector<std::string> emptyVec;

    m_desc.add_options()
            ("help,h", "This help")
            ("dir,d", po::value<VecStr>()->required()->multitoken(), "Directories for scanning")
            ("exclude,e", po::value<VecStr>()->multitoken(), "Directories for exclude")
            ("level,l", po::value<int>()->default_value(0), "Scan level: 0 (default) - only current directory, 1 - with subdirectories")
            ("filesize,f", po::value<std::size_t>()->default_value(1), "Min file size (in bytes, 1 by default) for checking")
            ("wildcards,w", po::value<VecStr>()->multitoken(), "Wildcards for compare. If isn't specified to use all files in directory")
            ("size,s", po::value<std::size_t>()->required(), "File reading's block size")
            ("alg,a", po::value<std::string>()->required(), "Checking's hash algorithm (crc32, md5)");
}

ParseResult CommandLineParser::parse(int argc, char **argv) {
    po::store(po::parse_command_line(argc, argv, m_desc), m_vm);

    if(m_vm.contains("help")) {
        return {Result::R_SHOWHELP, ""};
    }

    try {
        po::notify(m_vm);
    } catch (std::exception& e) {
        return {Result::R_BADCOMMAND, e.what()};
    }

    return {Result::R_SUCCESS, ""};
}

ParseParams CommandLineParser::getParseParams() const {
    return {m_vm["dir"].as<std::vector<std::string>>()
            , m_vm.contains("exclude") ? m_vm["exclude"].as<VecStr>() : VecStr()
            , m_vm["level"].as<int>()
            , m_vm["filesize"].as<std::size_t>()
            , m_vm.contains("wildcards") ? m_vm["wildcards"].as<VecStr>() : VecStr()
            , m_vm["size"].as<std::size_t>()
            , m_vm["alg"].as<std::string>()
    };
}

std::ostream &operator<<(std::ostream &os, const CommandLineParser &parse) {
    os << parse.m_desc;
    return os;
}


