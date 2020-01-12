cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS "--std=c++11 -Wall -ggdb -O0")

add_subdirectory(../fft fft)

set(FFT_N 64)
set(FFT_TYPE FpComplex)

include_directories(
  ../fft
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
  )

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_signals.cpp
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_signals.hpp
	COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../fft/tools/autogen_test_signals.py ${FFT_N} ${FFT_TYPE}
	)

add_executable(
  unit_test
  unit_test.cpp
  )

target_link_libraries(
  fft
  )

