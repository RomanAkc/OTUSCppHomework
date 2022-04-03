#pragma once
#include <boost/program_options.hpp>
#include <vector>
#include <string>

namespace po = boost::program_options;

enum class Result {
    R_SUCCESS,
    R_BADCOMMAND,
    R_SHOWHELP
};

struct ParseResult {
    Result result;
    std::string error;
};

struct ParseParams {
    std::vector<std::string> vecDir;
    std::vector<std::string> vecExclude;
    int scanLevel {0};
    std::size_t minFileSize {1};
    std::vector<std::string> vecWildcards;
    std::size_t blockSize {0};
    std::string algorithm;
};

class CommandLineParser {
    friend std::ostream& operator<<(std::ostream& os, const CommandLineParser& parse);

public:
    CommandLineParser();
    ParseResult parse(int argc, char ** argv);
    ParseParams getParseParams() const;

private:
    po::options_description m_desc{"Options"};
    po::variables_map m_vm;
};

