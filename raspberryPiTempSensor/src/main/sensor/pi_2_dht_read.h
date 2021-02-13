#ifndef PI_2_DHT_READ_H
#define PI_2_DHT_READ_H

#include "common_dht_read.h"

#ifdef __cplusplus
extern "C"{
#endif
// Read DHT sensor connected to GPIO pin (using BCM numbering).  Humidity and temperature will be 
// returned in the provided parameters. If a successful reading could be made a value of 0
// (DHT_SUCCESS) will be returned.  If there was an error reading the sensor a negative value will
// be returned.  Some errors can be ignored and retried, specifically DHT_ERROR_TIMEOUT or DHT_ERROR_CHECKSUM.
int pi_2_dht_read(int sensor, int pin, float* humidity, float* temperature);

#ifdef __cplusplus
}
#endif

#endif
