cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_FLAGS "-mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -fPIE -g")

add_library(common_dht_read_lib STATIC
	common_dht_read.c
        common_dht_read.h)
install(TARGETS common_dht_read_lib
	LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
	ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_library(pi_2_dht_read_lib STATIC
        pi_2_dht_read.c
        pi_2_dht_read.h)
target_link_libraries(pi_2_dht_read_lib PRIVATE
	common_dht_read_lib
	pi_2_mmio_lib)

install(TARGETS pi_2_dht_read_lib
	LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
	ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_library(pi_2_mmio_lib STATIC
        pi_2_mmio.c
        pi_2_mmio.h)
install(TARGETS pi_2_mmio_lib
	LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
	ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})


