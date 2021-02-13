//
// Created by David Halonen on 1/22/21.
//

#ifndef RASPBERRYPITEMPSENSOR_CORRELATIONFILE_H
#define RASPBERRYPITEMPSENSOR_CORRELATIONFILE_H

//This list of pair is the correlation between the Pi temp & the cooking thermometer temp.
//The 1st # is the pi reading.
//The 2nd # is the actual reading from the cooking thermometer.
//It is believed the 2nd # is the most accurate.
//By putting this in a macro, the data can be shared by both programs.
#define TEMP_MAP     static std::shared_ptr< std::vector< std::pair< float, float >>> \
        piThermometer ( new std::vector< std::pair< float, float >> ({  \
				{62.0, 66.0}, \
				{63.0, 73.0}, \
				{64.0, 77.0}, \
				{65.0, 80.0}, \
				{67.0, 89.0}, \
				{71.0, 97.0}, \
				{75.0, 104.0}, \
				{79.0, 111.0}, \
				{84.0, 117.0}, \
            {87.0, 120.0}, \
            {89.0, 122.0}, \
            {94.0, 130.0}, \
            {98.0, 134.0}, \
            {101.0, 134.0}, \
            {104.0, 140.0}, \
            {110.0, 148.0}, \
            {113.0, 149.0}, \
            {117.0, 155.0}, \
            {123.0, 156.0}, \
            {126.0, 158.0}, \
            {130.0, 163.0}, \
            {133.0, 166.0}, \
            {136.0, 169.0}, \
            {138.0, 170.0} \
        }));

#endif //RASPBERRYPITEMPSENSOR_CORRELATIONFILE_H
