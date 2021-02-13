//
// Created by David Halonen on 1/23/21.
//

#ifndef RASPBERRYPITEMPSENSOR_TEMPSENSOR_H
#define RASPBERRYPITEMPSENSOR_TEMPSENSOR_H

#include <memory>

#include "saunaPiData/SaunaPiDataFileSystem.h"
#include "saunaPiData/SaunaPiData.h"

typedef void (*loggerCallback)(std::string const &line);

class TempSensor {
public:
    explicit TempSensor(
            loggerCallback _logger
    );

    void readAndPublishFindings(
    );

private:
    SaunaPiDataFileSystem saunaPiFs;
    SaunaPiData saunaPiData;
    loggerCallback logger;

    void recordToTmpSaunaPiLog(
            float const humidity,
            float const temperature,
            float const thermometerTemp
    );

    void executePlot(
            std::string const &path,
            std::string const &highTempLabel,
            std::string const &currentTempLabel
    );
};
#endif //RASPBERRYPITEMPSENSOR_TEMPSENSOR_H
