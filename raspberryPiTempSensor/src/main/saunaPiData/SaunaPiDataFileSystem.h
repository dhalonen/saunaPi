//
// Created by David Halonen on 12/15/20.
//

#ifndef SAUNAPIDATATEST_SAUNAPIDATAFILESYSTEM_H
#define SAUNAPIDATATEST_SAUNAPIDATAFILESYSTEM_H

#include "SaunaPiDataFileSystemInterface.h"

class SaunaPiDataFileSystem: public SaunaPiDataFileSystemInterface {
public:
    SaunaPiDataFileSystem();

    bool is_directory(
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

    bool create_directory(
            std::string const &name
    ) override;

private:
    std::string filename;
};


#endif //SAUNAPIDATATEST_SAUNAPIDATAFILESYSTEM_H
