add_library(coolingFilter_lib STATIC
        CoolingFilter.cpp
        CoolingFilter.h)

install(TARGETS coolingFilter_lib
        LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
