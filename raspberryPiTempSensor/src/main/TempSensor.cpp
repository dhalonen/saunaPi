#include <cassert>
#include <filesystem>
#include <iostream>
extern "C" {
#include "sensor/pi_2_dht_read.h"
}
#include "TempSensor.h"

#include "correlationFile.h"
#include "simpleInterpolation.h"
TEMP_MAP
static simpleTools::interpolation <float, float> piThermInterp(piThermometer, 0.01);

TempSensor::TempSensor(
    CoolingFilter &filter,
    loggerCallback _logger
) :
    filter(filter),
    logger(_logger)
{
    saunaPiData.setFileSystem(&saunaPiFs);
}

void TempSensor::readAndPublishFindings(
) {
    float humidity = 0.0, temperature = 0.0;
    int readResult = pi_2_dht_read( AM2302, 4, &humidity, &temperature );
    if(readResult != DHT_SUCCESS )
    {
        std::string line { "error = " };
        line += std::to_string(readResult);
        logger(line);
    }
    else
    {
        assert(temperature > 0);
        assert(humidity > 0);
        temperature *= 1.8;     //Convert to Fahrenheit
        temperature += 32;
        auto thermometerTemp = piThermInterp.getY( temperature );

        if(std::get<0>(thermometerTemp) == simpleTools::InterpolationResultType::OK)
        {
            recordToTmpSaunaPiLog(&humidity, &temperature, &std::get<1>(thermometerTemp));
            performRecording(&std::get<1>(thermometerTemp), &humidity);
        } else {
            logger("Interpolation returned error.");
        }
    }
}

void TempSensor::performRecording(
        float *thermometerTemp,
        float *humidity
) {
    time_t now = time(&now);
    if(filter.accept(&now, (int) *thermometerTemp))
    {
        //returns success, data/png file path
        std::tuple<bool, std::string, std::string, std::string> addResults;
        addResults = saunaPiData.add(thermometerTemp, humidity);
        bool success;
        std::string path;
        std::string highTempLabel;
        std::string currentTempLabel;
        tie(success, path, highTempLabel, currentTempLabel) = addResults;
        if( !success )
        {
            logger("saunaPiData.add() failed.");
        }
        else
        {
            executePlot(path, highTempLabel, currentTempLabel);
        }
    }
}

void TempSensor::executePlot(
        std::string const &path,
        std::string const &highTempLabel,
        std::string const &currentTempLabel
) {
	if(path.length() > 0)
	{
	    std::string cmd = "/home/pi/saunaPi/saunaPiPlotter/createPlotCmd.sh ";
	    cmd += path + ".dat ";
	    cmd += path + ".png '";
	    cmd += highTempLabel + "' '";
	    cmd += currentTempLabel + "'";
	    //std::cout << "Command: " << cmd << "\n";
	    int cmdResult = system (cmd.c_str());
	    if(cmdResult != 0)
	    {
            logger("The plot command system result: " + std::to_string(cmdResult));
	    }
	    else
	    {
            cmd = "ln -s -f " + path + ".png /var/SaunaPiData/currentStatus.png";
            cmdResult = system (cmd.c_str());
            if(cmdResult != 0)
            {
                logger("The sym link system result: " + std::to_string(cmdResult));
            }
	    }
	}
}

void TempSensor::recordToTmpSaunaPiLog(
        float const *humidity,
        float const *temperature,
        float const *thermometerTemp
) {
    std::string line{"humidity = "};
    line += std::to_string((int) *humidity);
    line += "\t recorded temp = ";
    line += std::to_string((int) *temperature);
    line += "\t temperature = ";
    line += std::to_string((int) *thermometerTemp);
    line += "\t Optimal index (200 is ideal): ";
    line += std::to_string((int) (*humidity + *thermometerTemp));
    logger(line);
}
