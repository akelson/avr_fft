cmake_minimum_required(VERSION 3.14)

project(unit_test)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    runTest
    test_Complex.cpp
    test_FixedPoint.cpp
)

include_directories(../fft)

target_link_libraries(
    runTest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTest)
