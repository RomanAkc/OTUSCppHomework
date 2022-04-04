#pragma once
#include "objects.h"

class FilesComparator {
    // file -> [hash1, hash2, hash3, ...] (std::map<std::string, std::vector<hash>>


public:
    FilesComparator(const CompareParams &params);
    std::vector<std::vector<std::string>> run();

private:
    CompareParams m_params;
};