#pragma once
#include <filesystem>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include "objects.h"
#include "HashAlgorithm.h"


using VectorFiles = std::vector<std::filesystem::path>;
using FileGroups = std::map<std::size_t, VectorFiles>;

class FilesComparator {
public:
    FilesComparator(const CompareParams &params, const std::shared_ptr<IHashAlgorithm>& hashAlgorithm);
    std::vector<std::vector<std::string>> run();

private:
    CompareParams m_params;
    std::shared_ptr<IHashAlgorithm> m_hashAlgorithm;

    VectorFiles getFilesToCompare();

    template<class DirectoryIterator>
    VectorFiles getFilesForDirectory(DirectoryIterator& it) {
        VectorFiles filesForCheck;
        for(auto& el : it) {
            if(el.is_regular_file()) {
                filesForCheck.push_back(el.path());
            } else if (el.is_directory()) {
                // TO DO: check
            }
        }
        return filesForCheck;
    }

    FileGroups splitFilesBySize(const VectorFiles& files);
    std::size_t roundsizeToBlockSize(std::size_t size);

    std::vector<VectorFiles> compareFiles(std::size_t fileSize, const VectorFiles& files);
    std::vector<VectorFiles> compareFilesStep(const VectorFiles& files, std::map<std::filesystem::path, std::ifstream>& mapOpenedFiles
                                              , char* buffer, std::size_t readBufSize);
};