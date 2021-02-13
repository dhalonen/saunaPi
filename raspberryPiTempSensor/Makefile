#Makefile
all: build/saunaPiDataTest build/readSensor build/saunaPi

#Variables
CXX = g++
CXXFLAGS = -Wall -std=c++17 -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -fPIE -g
GCC = gcc
GCCFLAGS = -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -fPIE -g
# # We need -lsocket and -lnsl when on Solaris

READSENSOR_OBJS = build/common_dht_read.o \
		  build/readSensor.o \
		  build/pi_2_dht_read.o \
		  build/pi_2_mmio.o

SAUNAPI_OBJS = build/pi_2_dht_read.o \
	build/common_dht_read.o \
	build/pi_2_mmio.o \
	build/tempSensor.o \
	build/saunaPiData.o \
	build/saunaPiDataFileSystem.o \
	build/saunaPi.o

build/readSensor: $(READSENSOR_OBJS)
	${CXX} ${CXXFLAGS} -o $@ $^
	
build/saunaPi: $(SAUNAPI_OBJS)
	${CXX} -I/usr/include/arm-linux-gnueabihf/ -L/usr/lib/arm-linux-gnueabihf/8 -o $@ $^ -lstdc++fs

build/readSensor.o: src/main/readSensor.cpp src/main/sensor/pi_2_dht_read.h
	${CXX} ${CXXFLAGS} -o $@ -c src/main/readSensor.cpp

build/saunaPi.o: src/main/SaunaPi.cpp
	${CXX} ${CXXFLAGS} -o $@ -c src/main/SaunaPi.cpp

build/tempSensor.o: src/main/TempSensor.cpp src/main/sensor/pi_2_dht_read.h
	${CXX} ${CXXFLAGS} -o $@ -c src/main/TempSensor.cpp

build/pi_2_dht_read.o: src/main/sensor/pi_2_dht_read.h
	${GCC} ${GCCFLAGS} -o $@ -march=native -c src/main/sensor/pi_2_dht_read.c

build/common_dht_read.o: src/main/sensor/common_dht_read.h
	${GCC} ${GCCFLAGS} -o $@ -march=native -c src/main/sensor/common_dht_read.c

build/pi_2_mmio.o: src/main/sensor/pi_2_mmio.h
	${GCC} ${GCCFLAGS} -o $@ -march=native -c src/main/sensor/pi_2_mmio.c

build/saunaPiData.o: src/main/saunaPiData/SaunaPiData.h src/main/saunaPiData/SaunaPiData.cpp
	${CXX} ${CXXFLAGS} -o $@ -c src/main/saunaPiData/SaunaPiData.cpp

build/saunaPiDataFileSystem.o: src/main/saunaPiData/SaunaPiDataFileSystem.h src/main/saunaPiData/SaunaPiDataFileSystem.cpp
	${CXX} ${CXXFLAGS} -o $@ -c src/main/saunaPiData/SaunaPiDataFileSystem.cpp

build/saunaPiDataTest.o: src/main/saunaPiData/SaunaPiData.h \
	src/test/SaunaPiDataTest/saunaPiDataTest.cpp \
	src/test/SaunaPiDataTest/SaunaPiDataStubFileSystem.h \
	src/test/SaunaPiDataTest/SaunaPiDataStubFileSystem.cpp
	${CXX} ${CXXFLAGS} -o $@ -c src/test/SaunaPiDataTest/saunaPiDataTest.cpp

build/SaunaPiDataStubFileSystem.o: src/test/SaunaPiDataTest/SaunaPiDataStubFileSystem.h src/test/SaunaPiDataTest/SaunaPiDataStubFileSystem.cpp
	${CXX} ${CXXFLAGS} -o $@ -c src/test/SaunaPiDataTest/SaunaPiDataStubFileSystem.cpp

build/saunaPiDataTest: build/saunaPiData.o build/saunaPiDataTest.o build/SaunaPiDataStubFileSystem.o
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm build/*.o build/readSensor build/saunaPi build/saunaPiData/saunaPiDataTest

