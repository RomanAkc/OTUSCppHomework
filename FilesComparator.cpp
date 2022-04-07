#include "FilesComparator.h"
#include "md5.h"
#include "crc32.h"



FilesComparator::FilesComparator(const CompareParams &params)
    : m_params(params) {}

std::vector<std::vector<std::string>> FilesComparator::run() {
    auto filesToCompare = getFilesToCompare();

    if(filesToCompare.size() <= 1) {
        //nothing to compare
        return std::vector<std::vector<std::string>>();
    }

    //TODO: divide files by size









    return std::vector<std::vector<std::string>>();
}

VectorFiles FilesComparator::getFilesToCompare() {
    VectorFiles filesToCompare;

    bool withSubdir = m_params.scanLevel == 1;
    for(auto& dir : m_params.vecDir) {
        VectorFiles addFiles;
        if(withSubdir) {
            auto it = std::filesystem::recursive_directory_iterator(dir);
            addFiles = getFilesForDirectory(it);

        } else {
            auto it = std::filesystem::directory_iterator(dir);
            addFiles = getFilesForDirectory(it);
        }

        filesToCompare.insert(filesToCompare.end(), addFiles.begin(), addFiles.end());
    }

    std::sort(filesToCompare.begin(), filesToCompare.end());
    filesToCompare.erase(std::unique(filesToCompare.begin(), filesToCompare.end()), filesToCompare.end());
    return filesToCompare;
}
