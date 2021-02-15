cmake_minimum_required(VERSION 3.7)
project(raspberryPiTempSensor)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-Wall -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -fPIE -g")
set(CMAKE_CXX_FLAGS "-Wall  -fPIE -g")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_subdirectory(src/main/saunaPiData)
add_subdirectory(src/main/sensor)
add_subdirectory(src/main/coolingFilter)
add_subdirectory(src/test/SaunaPiDataTest)
add_subdirectory(src/test/CoolingFilterTest)

add_library(SaunaPi_lib STATIC
		src/main/SaunaPi.cpp)

add_executable(SaunaPi
		src/main/SaunaPi.cpp)

target_link_libraries(SaunaPi PRIVATE
        SaunaPi_lib
		tempSensor_lib
		pi_2_dht_read_lib
		pi_2_mmio_lib
		saunaPiData_lib
		-lc
		-lstdc++fs)

add_library(tempSensor_lib STATIC
		src/main/TempSensor.cpp
		src/main/simpleInterpolation.h
		src/main/correlationFile.h src/main/coolingFilter/CoolingFilter.cpp src/main/coolingFilter/CoolingFilter.h)

add_executable(readSensor
        src/main/readSensor.cpp
		src/main/correlationFile.h)

add_library(readSensor_lib STATIC
        src/main/readSensor.cpp)

target_link_libraries(readSensor PRIVATE
        pi_2_dht_read_lib
        pi_2_mmio_lib
		-lc)
