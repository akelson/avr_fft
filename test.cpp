#include <math.h>

#include <iostream>
#include <complex>
#include <cstdint>
#include <vector>

#include "Complex.hpp"
#include "FixedPoint.hpp"

#include "Fft.hpp"


static const size_t N = 64;

using Fp = FixedPoint<int16_t, 8>;
using FpComplex = Complex<Fp>;

#include "twiddle_factors_64.cpp"

template<>
FpComplex ConvertTwiddleFactor<FpComplex>(const int16_t value)
{
    return FpComplex(Fp::Make(value>>7));
}

std::vector<FpComplex> MakeSamples(const size_t size, const int freq)
{
    std::vector<FpComplex> out;
    for (size_t i = 0; i < size; i++)
    {
        const double angle = 2*M_PI*i*freq/size;
        const double value = sin(angle);
        Fp fp(value);
        FpComplex fpc(fp);
        out.push_back(fpc);
    }
    return out;
}

int main(void)
{
    std::vector<FpComplex> x1 = MakeSamples(N,4);
    for (int i = 0; i < N; i++)
    {
        //std::cout << x1[i] << std::endl;
    }

    Fft<FpComplex,N>::ditfft(x1.data(),N);

    for (int i = 0; i < N; i++)
    {
        std::cout << x1[i] << std::endl;
    }
} // end main
