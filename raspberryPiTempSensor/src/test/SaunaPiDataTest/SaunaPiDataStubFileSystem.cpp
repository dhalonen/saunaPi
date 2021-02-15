//
// Created by David Halonen on 12/6/20.
//

#include <iostream>

#include "SaunaPiDataStubFileSystem.h"

SaunaPiDataStubFileSystem::SaunaPiDataStubFileSystem()
{
    items.emplace("/var/SaunaPiData", "dir");
}

bool SaunaPiDataStubFileSystem::is_directory(
        std::string const &name
) {
    return isInMap(name, "dir");
}

bool SaunaPiDataStubFileSystem::isInMap(
        std::string const &name,
        std::string const &type
) {
    auto search = items.find(name);
    if(search == items.end() )
    {
        return false;
    }

    if( search->second == type)
    {
        return true;
    }
    return false;
}

bool SaunaPiDataStubFileSystem::create_directory(
        std::string const &name
) {
    items.emplace(name, "dir");
    return true;
}

bool SaunaPiDataStubFileSystem::exists(
        std::string const &name,
        std::string const &type
) {
    return isInMap(name, type);
}

bool SaunaPiDataStubFileSystem::createFile(
        std::string const &name
) {
    items.emplace(name, "file");
    return true;
}

bool SaunaPiDataStubFileSystem::writeData(
        std::string const &data
) {
    items.emplace(data, "data");
    return true;
}

void SaunaPiDataStubFileSystem::dump() const
{
    for (auto &it : items) {
        std::cout << it.first << ", " << it.second << '\n';
    }
}
