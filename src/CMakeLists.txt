cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -ggdb -O0")

project(FFT VERSION 1.0)

set(FFT_N 64)
set(FFT_TYPE FpComplex)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/twiddle_factors.cpp
	COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../tools/autogen_twiddle_factors.py ${FFT_N} ${FFT_TYPE}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_signals.cpp
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_signals.hpp
	COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../tools/autogen_test_signals.py ${FFT_N} ${FFT_TYPE}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(unit_test
	test.cpp
	${CMAKE_CURRENT_BINARY_DIR}/twiddle_factors.cpp
	${CMAKE_CURRENT_BINARY_DIR}/test_signals.cpp
)
