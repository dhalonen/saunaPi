add_executable(saunaPiDataTests
        saunaPiDataTest.cpp
        SaunaPiDataStubFileSystem.cpp
        SaunaPiDataStubFileSystem.h
        ../include/catch.hpp)
target_link_libraries(saunaPiDataTests PRIVATE
        saunaPiData_lib)

install(TARGETS saunaPiDataTests
	RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

