//
// Created by David Halonen on 12/6/20.
//
#include <string>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../include/catch.hpp"

#include "../../main/saunaPiData/SaunaPiData.h"
#include "SaunaPiDataStubFileSystem.h"

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    SaunaPiDataStubFileSystem testFileSystem;
    SaunaPiData doesntExistDataDir("/var/doesntExist");
    float temp = 121.0, humidity = 20.0; //MIN_TEMPERATURE = 120 in SaunaPiData.cpp
    //Ensure a non-existent dir is caught
    //TODO fix this REQUIRE_FALSE( doesntExistDataDir.add(&temp, &humidity) );

    SaunaPiData data;
    data.setFileSystem(&testFileSystem);
    std::string rootDataDir = data.getRootDataDir();
    //Here we are ensuring the assumed /var/SaunaPiData dir is in place
    time_t rawtime = time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);

    //add() does a lot:
    // ensures root data dir exists
    // ensures the year data dir exists, creates if not
    // ensures the month data dir exists, creates if not
    // ensures today's data file exists, creates if not
    // writes timestamp, temperature, humidity, & optimal value to data file
	std::tuple<bool, std::string, std::string, std::string> addResults;
	addResults = data.add(&temp, &humidity, timeinfo);
	bool success;
	std::string path;
	std::string highTempLabel;
	std::string currentTempLabel;
	std::tie(success, path, highTempLabel, currentTempLabel) = addResults;
    //data.add(&temp, &humidity, timeinfo);
    testFileSystem.dump();
    std::tuple<std::string, std::string, std::string> result;
    result = data.currentYearMonthDay(timeinfo);
    std::string year;
    std::string month;
    std::string day;
    std::tie(year, month, day) = result;

    std::string yearDir(rootDataDir);
    yearDir += "/";
    yearDir += year;
    REQUIRE(testFileSystem.is_directory(yearDir)); //the year dir is in place
    std::string monthDir(yearDir);
    monthDir += "/";
    monthDir += month;
    REQUIRE(testFileSystem.is_directory(monthDir)); //the month dir is in place

    std::string dayfile(monthDir);
    dayfile += "/";
    dayfile += year;
    dayfile += "-";
    dayfile += month;
    dayfile += "-";
    dayfile += day;
    dayfile += ".dat";
    REQUIRE(testFileSystem.exists(dayfile, "file")); //today's data file is in place
    //REQUIRE - data file contains the added line
    //data2.add(&temp, &humidity); //TODO add time delay
    //REQUIRE - data file contains 2 lines, the last == last added

    //For posterity, lets see what the file system holds:
    testFileSystem.dump();
}
