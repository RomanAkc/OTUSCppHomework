#include <map>
#include "FilesComparator.h"
//#include "md5.h"
#include "crc32.h"



FilesComparator::FilesComparator(const CompareParams &params)
    : m_params(params) {}

std::vector<std::vector<std::string>> FilesComparator::run() {
    auto filesToCompare = getFilesToCompare();

    if(filesToCompare.size() <= 1) {
        //nothing to compare
        return std::vector<std::vector<std::string>>();
    } /*else if (filesToCompare.size() == 1) {
        return {{filesToCompare[0]}};
    }*/

    auto filesBySize = splitFilesBySize(filesToCompare);












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

FileGroups FilesComparator::splitFilesBySize(const VectorFiles& files) {
    FileGroups groups;
    for(auto& file : files) {
        //auto size = roundsizeToBlockSize(std::filesystem::file_size(file));
        auto size = std::filesystem::file_size(file);
        groups[size].push_back(file);
    }
    return groups;
}

std::size_t FilesComparator::roundsizeToBlockSize(std::size_t size) {
    if(size < m_params.blockSize) {
        size = m_params.blockSize;
    } else {
        auto rest = size % m_params.blockSize;
        if(rest != 0)
            size += rest;
    }
    return size;
}

std::vector<VectorFiles> FilesComparator::compareFiles(std::size_t fileSize, const VectorFiles &files) {
    if(files.empty() || files.size() == 1) {
        return {};
    }

    std::size_t iterCount = fileSize / m_params.blockSize + (fileSize % m_params.blockSize != 0 ? 1 : 0);

    char* buffer = new char[m_params.blockSize];

    std::map<std::filesystem::path, std::ifstream> mapOpenedFiles;
    for(auto& file : files) {
        mapOpenedFiles.emplace(file, std::ifstream(file, std::ios_base::binary));
        //mapOpenedFiles[file].open(file, std::ios_base::binary);
    }

    std::vector<VectorFiles> vecResult;

    for(std::size_t i = 0; i < iterCount; ++i) {
        std::size_t readBufSize = (i == iterCount - 1) ? fileSize % m_params.blockSize : m_params.blockSize;
        if(i == 0) {
            vecResult = compareFilesStep(files, mapOpenedFiles, buffer, readBufSize);
        } else {
            if(vecResult.empty()) {
                break;
            }

            std::vector<VectorFiles> vecNewResults;
            for(auto& vfiles : vecResult) {
                auto res = compareFilesStep(vfiles, mapOpenedFiles, buffer, readBufSize);
                std::copy(res.begin(), res.end(), std::back_inserter(vecNewResults));
            }
            vecResult = std::move(vecNewResults);
        }
    }

    delete[] buffer;
    return vecResult;
}

std::vector<VectorFiles> FilesComparator::compareFilesStep(const VectorFiles& files, std::map<std::filesystem::path, std::ifstream>& mapOpenedFiles
        , char* buffer, std::size_t readBufSize) {

    std::map<std::string, VectorFiles> mapHashToFile;
    for(auto& file : files) {
        mapOpenedFiles[file].read(buffer, readBufSize);

        //TODO: to use differenf alg
        auto s = crc32(buffer);

        mapHashToFile[s].push_back(file);
    }

    std::vector<VectorFiles> vecResult;
    for(auto& [hash, vecFiles] : mapHashToFile) {
        if(vecFiles.size() <= 1)
            continue;

        vecResult.push_back(vecFiles);
    }

    return vecResult;
}


