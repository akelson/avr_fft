#include <math.h>

#include <iostream>
#include <iomanip>
#include <complex>
#include <cstdint>
#include <vector>

#include "Complex.hpp"
#include "FixedPoint.hpp"

#include "Fft.hpp"


static const size_t N = 64;

using Fp = FixedPoint<int16_t, 10>;
using FpComplex = Complex<Fp>;

#include "twiddle_factors_64.cpp"

template<>
FpComplex ConvertTwiddleFactor<FpComplex>(const int16_t value)
{
    return FpComplex(Fp::Make(value>>5));
}

void AddSignal(std::vector<FpComplex>& x, const int freq)
{
    for (size_t i = 0; i < x.size(); i++)
    {
        const double angle = 2*M_PI*i*freq/x.size();
        const double value = sin(angle);
        Fp fp(value);
        FpComplex fpc(fp);
        x[i] = x[i] + fpc;
    }
}

int main(void)
{
    std::vector<FpComplex> x1(N);
    AddSignal(x1, 8);
    AddSignal(x1, 16);
    AddSignal(x1, 5);
    for (int i = 0; i < N; i++)
    {
        //std::cout << x1[i] << std::endl;
    }

    Fft<FpComplex,N>::ditfft(x1.data(),N);

    for (int i = 0; i < N/2; i++)
    {
        //std::cout << i << ": " << x1[i].re_ << std::endl;
        int dots = x1[i].re_.toDouble();
        std::cout << std::setw(2) << i << " ";
        for (int j = 0; j < dots; j++)
        {
            std::cout << ".";
        }
        std::cout << std::endl;
    }
} // end main
