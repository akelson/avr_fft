#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include "FixedPoint.hpp"

constexpr size_t N = 64;
constexpr int F = 8;
using Fp = FixedPoint<int16_t, F>;
using FpComplex = Complex<Fp>;

#endif  // COMMONTYPES_H
