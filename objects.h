#pragma once
#include <vector>
#include <string>

enum class Result {
    R_SUCCESS,
    R_BADCOMMAND,
    R_SHOWHELP
};

struct ParseResult {
    Result result;
    std::string error;
};

struct CompareParams {
    std::vector<std::string> vecDir;
    std::vector<std::string> vecExclude;
    int scanLevel {0};
    std::size_t minFileSize {1};
    std::vector<std::string> vecWildcards;
    std::size_t blockSize {1};
    std::string algorithm;
};
