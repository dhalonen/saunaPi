//
// Created by David Halonen on 12/6/20.
//
#ifndef RASPBERRYPITEMPSENSOR_SAUNAPIDATASTUBFILESYSTEM_H
#define RASPBERRYPITEMPSENSOR_SAUNAPIDATASTUBFILESYSTEM_H

#include <map>
#include <string>

#include "../../main/saunaPiData/SaunaPiData.h"

class SaunaPiDataStubFileSystem: public SaunaPiDataFileSystemInterface {
public:
    SaunaPiDataStubFileSystem();

    bool is_directory(
            std::string const &name
    ) override;

    bool create_directory(
            std::string const &name
    ) override;

    bool exists(
            std::string const &name,
            std::string const &type
    ) override;

    bool createFile(
            std::string const &name
    ) override;

    bool writeData(
            std::string const &data
    ) override;

    void dump() const;

private:
    std::map<std::string, std::string> items;

    bool isInMap(
            const std::string &name,
            const std::string &type
    );
};

#endif //RASPBERRYPITEMPSENSOR_SAUNAPIDATASTUBFILESYSTEM_H
