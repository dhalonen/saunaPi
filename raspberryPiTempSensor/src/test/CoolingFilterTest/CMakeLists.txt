add_executable(coolingFilterTest
        coolingFilterTest.cpp
        ../include/catch.hpp)
target_link_libraries(coolingFilterTest PRIVATE
        coolingFilter_lib)

install(TARGETS coolingFilterTest
        RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

