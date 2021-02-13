add_library(saunaPiData_lib STATIC
        SaunaPiData.cpp
        SaunaPiData.h
        SaunaPiDataFileSystem.cpp
        SaunaPiDataFileSystem.h
        SaunaPiDataFileSystemInterface.h)

install(TARGETS saunaPiData_lib
	LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
	ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
