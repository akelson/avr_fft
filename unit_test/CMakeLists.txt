cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../fft)

add_executable(runTest test.cpp)
target_link_libraries(runTest ${GTEST_LIBRARIES} pthread)
