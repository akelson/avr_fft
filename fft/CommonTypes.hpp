#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#ifdef __AVR__
#include <stdlib.h>
#include <avr/io.h>
#else
#include <cstdint>
#endif

#include "FixedPoint.hpp"
#include "Complex.hpp"

constexpr size_t N = 64;
constexpr int F = 8;
using Fp = FixedPoint<int16_t, F>;
using FpComplex = Complex<Fp>;

#endif  // COMMONTYPES_H
