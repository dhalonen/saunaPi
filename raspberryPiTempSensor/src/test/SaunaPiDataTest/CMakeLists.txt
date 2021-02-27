add_executable(saunaPiDataTests
        saunaPiDataTest.cpp
        SaunaPiDataStubFileSystem.cpp
        SaunaPiDataStubFileSystem.h
        ../include/catch.hpp
		MainSaunaPiDataTest.cpp)
target_link_libraries(saunaPiDataTests PRIVATE
        saunaPiData_lib)

install(TARGETS saunaPiDataTests
	RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

