//
// Created by David Halonen on 12/5/20.
//

#ifndef RASPBERRYPITEMPSENSOR_SAUNAPIDATA_H
#define RASPBERRYPITEMPSENSOR_SAUNAPIDATA_H

#include <fstream>
#include <string>
#include <tuple>

#include "SaunaPiDataFileSystemInterface.h"

class SaunaPiData{
public:
    explicit SaunaPiData(
            std::string rootDataDir = "/var/SaunaPiData"
    );

    void setFileSystem(
            SaunaPiDataFileSystemInterface *_fs
    );

    //Normal usage is to have timeinfo = nullptr. However, for testing it makes sense to have this as input.
    std::tuple<bool, std::string, std::string, std::string> add(
            float const *temp,
            float const *humidity,
            struct tm *timeinfo = nullptr
    );

    std::tuple<std::string, std::string, std::string> currentYearMonthDay(
            struct tm const * const timeinfo
    );

    std::string getRootDataDir() const;

private:
    SaunaPiDataFileSystemInterface *fs;
    std::string rootDataDir;
    std::string year;
    std::string month;
    std::string monthNumber;
    std::string day;
    std::string hour;
    std::string minute;
    std::string hourMinuteForUser;
    int highTemp;
    std::string highTempNote;
    std::fstream data;

    void setYearAndMonth(
            tm const * const timeinfo
    );

    std::string getHighTempLabel(
        int const temp
    );
};


#endif //RASPBERRYPITEMPSENSOR_SAUNAPIDATA_H
