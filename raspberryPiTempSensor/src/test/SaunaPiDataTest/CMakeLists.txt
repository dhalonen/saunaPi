add_executable(saunaPiDataTests
		saunaPiDataTest.cpp
)

add_library(saunaPiDataTests_lib STATIC
		saunaPiDataTest.cpp
        SaunaPiDataStubFileSystem.cpp
        SaunaPiDataStubFileSystem.h
        ../include/catch.hpp
		MainSaunaPiDataTest.cpp)

target_link_libraries(saunaPiDataTests PRIVATE
		saunaPiDataTests_lib
        saunaPiData_lib)

install(TARGETS saunaPiDataTests_lib
		LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
		ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

install(TARGETS saunaPiDataTests
	RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

