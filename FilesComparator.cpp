#include "FilesComparator.h"
#include <filesystem>
#include <set>
#include "md5.h"
#include "crc32.h"

namespace fs = std::filesystem;

FilesComparator::FilesComparator(const CompareParams &params)
    : m_params(params) {}

std::vector<std::vector<std::string>> FilesComparator::run() {
    std::set<fs::path> checkedPaths;
    std::set<fs::path> checkedFiles;

    //bool bCheckSubFolder = m_params.scanLevel == 1;
    for(auto& dir : m_params.vecDir) {
        auto p = fs::path(dir);
        for(auto& el : fs::directory_iterator(p)) {
            bool b1 = el.is_directory();
            bool b2 = el.is_regular_file();

            if(b1)
                checkedPaths.insert(el.path());

            if(b2)
                checkedFiles.insert(el.path());

        }


    }






    return std::vector<std::vector<std::string>>();
}
