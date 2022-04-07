#pragma once
#include "objects.h"
#include <filesystem>
#include <set>
#include <vector>

using VectorFiles = std::vector<std::filesystem::path>;

class FilesComparator {
    // file -> [hash1, hash2, hash3, ...] (std::map<std::string, std::vector<hash>>

public:
    FilesComparator(const CompareParams &params);
    std::vector<std::vector<std::string>> run();

private:
    CompareParams m_params;

    VectorFiles getFilesToCompare();

    template<class DirectoryIterator>
    VectorFiles getFilesForDirectory(DirectoryIterator& it) {
        VectorFiles filesForCheck;
        for(auto& el : it) {
            if(el.is_regular_file()) {
                filesForCheck.push_back(el.path());
            }
        }
        return filesForCheck;
    }
};