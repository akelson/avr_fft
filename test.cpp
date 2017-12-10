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

void AddSignal(std::vector<FpComplex>& x, 
    const double amplitude, const int freq, const int phase)
{
    for (size_t i = 0; i < x.size(); i++)
    {
        const double angle = 2*M_PI*i*freq/x.size();
        const double value = amplitude*sin(angle+phase);
        Fp fp(value);
        FpComplex fpc(fp);
        x[i] = x[i] + fpc;
    }
}

void Disp(const std::vector<FpComplex>& x, int scale, int dc)
{
    for (int i = 0; i < x.size()/2; i++)
    {
        //std::cout << i << ": " << x1[i].re_ << std::endl;
        double re = x[i].re_.toDouble();
        double im = x[i].im_.toDouble();
        double magnitude = 
            sqrt(re*re + im*im);
        int dots = dc + scale * magnitude;
        std::cout << std::setw(2) << i << " ";
        for (int j = 0; j < dots; j++)
        {
            std::cout << ".";
        }
        std::cout << std::endl;
    }
}

int main(void)
{
    std::vector<FpComplex> x1(N);
    //AddSignal(x1, 8);
    AddSignal(x1, 1, 8, 0);
    AddSignal(x1, 1, 16, 0);
    AddSignal(x1, .5, 30, 0);
    //AddSignal(x1, 5, 3);

    //Disp(x1,5,10);
    std::cout << std::endl;

    for (int i = 0; i < N; i++)
    {
        //std::cout << x1[i] << std::endl;
    }

    //Fft<FpComplex,N>::PrintTwiddleFactors();

    Fft<FpComplex,N>::ditfft(x1.data(),N);

    Disp(x1,1,0);

    for (int i = 0; i < x1.size()/2; i++)
    {
        //std::cout << x1[i] << std::endl;
    }

} // end main

