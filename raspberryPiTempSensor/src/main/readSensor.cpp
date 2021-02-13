/** 
 * The simple tool to get the current humidity & temperature. Basically, this is used to ensure simplest functionality.
 * It simply performs a single read of the sensor, records the values (temperature is adjusted), and quits.
 *
 */
#include <ctime>
#include <iomanip>
#include <iostream>

#include "correlationFile.h"
extern "C" {
   #include "sensor/pi_2_dht_read.h"
}
#include "simpleInterpolation.h"


int main()
{
    TEMP_MAP
    simpleTools::interpolation <float, float> piThermInterp( piThermometer  );
    float humidity = 0.0, temperature = 0.0;
    int sensorReadResult = pi_2_dht_read(AM2302, 4, &humidity, &temperature );
    if(sensorReadResult == -4 )
    {
        std::cout << "Unable to read sensor. Try executing this as \'sudo\'.\n";
    }
    else if(sensorReadResult == DHT_SUCCESS)
    {
        temperature *= 1.8;     //Convert to Fahrenheit
        temperature += 32;
        auto thermometerTemp = piThermInterp.getY( temperature );
        std::time_t t = std::time( nullptr );
        std::cout << std::put_time( std::localtime( &t ), "%c %Z" ) << "\t";
        std::cout << "humidity = " << (int) humidity << "\t";
        std::cout << "recorded temp = ";
        std::cout << (int) temperature;
        std::cout << "temperature = " << (int) thermometerTemp << "\t";
        std::cout << "Optimal index (200 is ideal): " << (int) (humidity + thermometerTemp) << "\n";
    }
    else
    {
        std::cout << "Error #: " << sensorReadResult << " received.";
    }
    return 0;
}

