cmake_minimum_required (VERSION 3.0)

project(FFT VERSION 1.0)

set(FFT_N 64)
set(FFT_TYPE FpComplex)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/twiddle_factors.cpp
	COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/tools/autogen_twiddle_factors.py ${FFT_N} ${FFT_TYPE}
	)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	)

add_library(fft STATIC
	${CMAKE_CURRENT_BINARY_DIR}/twiddle_factors.cpp
	)
