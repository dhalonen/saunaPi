//
// Created by David Halonen on 12/6/20.
//

#ifndef RASPBERRYPITEMPSENSOR_SAUNAPIDATAFILESYSTEMINTERFACE_H
#define RASPBERRYPITEMPSENSOR_SAUNAPIDATAFILESYSTEMINTERFACE_H

#include <string>

class SaunaPiDataFileSystemInterface {
public:
    virtual bool is_directory(
            std::string const &name
    ) = 0;

    virtual bool create_directory(
            std::string const &name
    ) = 0;

    virtual bool exists(
            std::string const &name,
            std::string const &type
    ) = 0;

    virtual bool createFile(
            std::string const &name
    ) = 0;

    virtual bool writeData(
            std::string const &data
    ) = 0;
};
#endif //RASPBERRYPITEMPSENSOR_SAUNAPIDATAFILESYSTEMINTERFACE_H
