//
// Created by David Halonen on 12/15/20.
//

#include <iostream>
#include <filesystem>
#include <fstream>

#include "SaunaPiDataFileSystem.h"

SaunaPiDataFileSystem::SaunaPiDataFileSystem() = default;

bool SaunaPiDataFileSystem::is_directory(
        std::string const &name
) {
    return std::filesystem::is_directory(name);
}

bool SaunaPiDataFileSystem::create_directory(
        std::string const &name
) {
    return std::filesystem::create_directory(name);
}

bool SaunaPiDataFileSystem::exists(
        std::string const &name,
        std::string const &type
) {
    return std::filesystem::exists(name);
}

bool SaunaPiDataFileSystem::createFile(
        std::string const &name
) {
    filename = name;
    return true;
}

bool SaunaPiDataFileSystem::writeData(
        std::string const &data
) {
    std::ofstream ofs(filename.c_str(), std::ofstream::app);
    ofs << data << "\n";
    ofs.close();
    ofs << std::unitbuf; // enable automatic flushing
    return true;
}
