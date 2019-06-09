cmake_minimum_required (VERSION 3.0)

set(FFT_N 64)
set(FFT_TYPE FpComplex)

set(MCU atmega328)
set(F_CPU 1000000UL)

add_definitions(
  -fno-threadsafe-statics
  -std=c++11
  -Wall
  -ggdb
  -Os
  -mmcu=${MCU}
  -DF_CPU=${F_CPU}
  -DAVR
  )

add_subdirectory(../fft fft)

set(PROGRAMMER = stk500)

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
  avr_test
  avr_test.cpp
  test_signals.cpp
  )

target_link_libraries(
  avr_test
  fft
  )

