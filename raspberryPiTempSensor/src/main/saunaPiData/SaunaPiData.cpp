//
// Created by David Halonen on 12/5/20.
//

#include <cassert>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <cstring>

#include "SaunaPiData.h"

const float MIN_TEMPERATURE = 120.0;

SaunaPiData::SaunaPiData(
        std::string rootDataDir):
        rootDataDir(std::move(rootDataDir)),
        highTemp(0),
        highTempNote("")
{ };

void SaunaPiData::setFileSystem(
        SaunaPiDataFileSystemInterface *_fs
) {
    fs = _fs;
}

/*
 * Write out time, temp, humidity, and optimal value in following format:
 * 12/14/2020-22:40 67 41 108
 * Month, day, hours, & minutes are all 2 digits.
 * The values are separated by space chars.
 * Temp, humidity, & optimal values have single digit precision (no fractions.)
 */
std::tuple<bool, std::string, std::string, std::string> SaunaPiData::add(
        float const *temp,
        float const *humidity,
        struct tm *timeinfo
) {
    if(*temp < MIN_TEMPERATURE)
    {
        highTemp = 0;
	    return std::make_tuple(true, "", "", "");
    }
    
    if(!fs->is_directory(rootDataDir)) {
	    std::cout << "rootDataDir: " << rootDataDir << "\n";
	    return std::make_tuple(false, "", "", "");
    }

    //Does the current year exist in rootDataDir?
    setYearAndMonth(timeinfo);
    std::string yearDir(rootDataDir);
    yearDir += "/";
    yearDir += year;

    if(!fs->is_directory(yearDir))
    {
        if(!fs->create_directory(yearDir))
        {
	    std::cout << "yearDir: " << yearDir << "\n";
	    return std::make_tuple(false, "", "", "");
        }
    }

    std::string monthDir(yearDir);
    monthDir += "/";
    monthDir += month;

    if(!fs->is_directory(monthDir))
    {
        if(!fs->create_directory(monthDir))
        {
	    std::cout << "monthDir: " << monthDir << "\n";
	    return std::make_tuple(false, "", "", "");
        }
    }

    std::string dayfile(monthDir);
    dayfile += "/";
    dayfile += year;
    dayfile += "-";
    dayfile += month;
    dayfile += "-";
    dayfile += day;
    std::string path = dayfile;	//keep path for plotter
    dayfile += ".dat";

    if(!fs->createFile(dayfile))
    {
	    std::cout << "failed to create file.\n";
	    return std::make_tuple(false, "", "", "");
    }
    char buffer[100];
    sprintf(buffer, " %.0f %.0f %.0f", *temp, *humidity, *temp + *humidity);
    std::string data(monthNumber + "/" + day + "/" + year + "-" + hour + ":" + minute + buffer);
    return std::make_tuple(
            fs->writeData(data),
            path,
            getHighTempLabel((int) *temp),
            std::to_string((int) (*temp)) + " at " + hourMinuteForUser);
}

std::string SaunaPiData::getHighTempLabel(
        int const temp
) {
    //TODO is the following block ever executed?
     if(temp < (int) MIN_TEMPERATURE)
     {
         return std::string("");
     }
     if(temp > highTemp)
     {
         highTemp = temp;
         highTempNote = "High temp: " + std::to_string(highTemp) + " at " + hourMinuteForUser;
     }
     return highTempNote;
}

void SaunaPiData::setYearAndMonth(
        tm const * const timeinfo
) {
    //Get time
    struct tm timecopy;
    if(timeinfo == nullptr)
    {
        time_t rawtime = time(&rawtime);
        memcpy((void *) &timecopy, localtime(&rawtime), sizeof(struct tm));
    } else {
        memcpy((void *) &timecopy, (void *)timeinfo, sizeof(struct tm));
    }
    std::tuple<std::string, std::string, std::string> result;
    result = currentYearMonthDay(&timecopy);
    std::string extra;
    std::tie(year, month, extra) = result;
}

std::tuple<std::string, std::string, std::string> SaunaPiData::currentYearMonthDay(
        struct tm const * const timeinfo
) {
    std::string yr, mnth;

    yr = std::to_string(1900 + timeinfo->tm_year);
    monthNumber = std::to_string(timeinfo->tm_mon + 1);
    hour = std::to_string(timeinfo->tm_hour);
    minute = std::to_string(timeinfo->tm_min);
    hourMinuteForUser = std::to_string(timeinfo->tm_hour > 12 ? timeinfo->tm_hour - 12 : timeinfo->tm_hour) + ":";
    if(timeinfo->tm_min < 10)
    {
        hourMinuteForUser += "0";
    }
    hourMinuteForUser += std::to_string(timeinfo->tm_min);

    switch( timeinfo->tm_mon ) {
        case 0:
            mnth = "Jan";
	    break;
        case 1:
            mnth = "Feb";
	    break;
        case 2:
            mnth = "Mar";
	    break;
        case 3:
            mnth = "Apr";
	    break;
        case 4:
            mnth = "May";
	    break;
        case 5:
            mnth = "Jun";
	    break;
        case 6:
            mnth = "Jul";
	    break;
        case 7:
            mnth = "Aug";
	    break;
        case 8:
            mnth = "Sep";
	    break;
        case 9:
            mnth = "Oct";
	    break;
        case 10:
            mnth = "Nov";
	    break;
        case 11:
            mnth = "Dec";
	    break;
        default:
            assert(0);
    }

    day = std::to_string(timeinfo->tm_mday);

    return std::make_tuple(yr, mnth, day);
}

std::string SaunaPiData::getRootDataDir() const
{
    return rootDataDir;
}
