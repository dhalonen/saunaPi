//
// Created by David Halonen on 1/23/21.
//
//TODO incorporate corrected temp value map

//TODO add ASSERTs
//TODO ensure refs are used, not copy object
//TODO review Meyer's guidance
//TODO fuzz testing
//TODO SourceTrail on code
//TODO try diff compilers: C++ 11, 14, 17, 20 (where possible)

//TODO stub sensor for unit testing
//TODO create single project w/ three sub-projects on GitHub
//TODO update to newer version of simpleInterpolation
//TODO create config file for datafile location, minTemp, console, data only - if these are kept
//TODO update SauanPiData to return values other than just success/fail

//TODO launch app on pi startup
//TODO create means to ensure only one copy is executing: pid file?

//TODO create interface in case another sensor is needed

//TODO time label - 12 hr clock, leading zero on minutes ie, 7:09

#include <csignal>
#include <ctime>
//Keep <iomanip> it's needed.
#include <iomanip>
#include <unistd.h>

#include "TempSensor.h"

void logToTmpSaunaPiLog(
        std::string const &line
);

int run = 1;
void signalHandler(
        int signum
) {
    run = 0;
}

void signalSetup(){
    std::signal(SIGABRT, signalHandler);
    std::signal(SIGFPE, signalHandler);
    std::signal(SIGILL, signalHandler);
    std::signal(SIGINT, signalHandler);
    std::signal(SIGSEGV, signalHandler);
    std::signal(SIGTERM, signalHandler);
}

int main(
) {
    TempSensor tempSensor(logToTmpSaunaPiLog);
    signalSetup();
    while(run)
    {
        tempSensor.readAndPublishFindings();
        sleep( 15 ); //sleep( seconds )
    }
    return 0;
}

void logToTmpSaunaPiLog(
        std::string const &line
) {
    std::ofstream ofs("/tmp/saunapi.log", std::ios_base::app);
    time_t t = time( nullptr );
    ofs << std::put_time( localtime( &t ), "%c %Z" ) << "\t";
    ofs << line << "\n";
    ofs.close();
    ofs << std::unitbuf; // enable automatic flushing
}
