#pragma once
#include <boost/program_options.hpp>
#include "objects.h"

namespace po = boost::program_options;

class CommandLineParser {
    friend std::ostream& operator<<(std::ostream& os, const CommandLineParser& parse);

public:
    CommandLineParser();
    ParseResult parse(int argc, char ** argv);
    CompareParams getParseParams() const;

private:
    po::options_description m_desc{"Options"};
    po::variables_map m_vm;
};

