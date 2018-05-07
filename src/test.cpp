#include <math.h>

#include <iostream>
#include <iomanip>
#include <complex>
#include <cstdint>
#include <vector>

#include "Complex.hpp"
#include "FixedPoint.hpp"

#include "Fft.hpp"


static const size_t N = 8;

using Fp = FixedPoint<int16_t, 8>;
using FpComplex = Complex<Fp>;

#include "autogen/twiddle_factors_8.cpp"
#include "autogen/test_signal_8.cpp"

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

void Assert(const bool pass, std::string msg)
{
    if (pass)
    {
        std::cout << "PASS - ";
    }
    else
    {
        std::cout << "FAIL - ";
    }
    std::cout << msg << std::endl;
}

bool TestFixedPoint()
{
    // Constructor
    FixedPoint<int16_t,0> a0(1.0);
    Assert(0x0001 == a0.value_,"Constructor 1");

    FixedPoint<int16_t,8> a8(1.0);
    Assert(0x0100 == a8.value_,"Constructor 2");

    FixedPoint<int16_t,14> a16(1.0);
    Assert(0x4000 == a16.value_,"Constructor 3");

    // Assignment
    FixedPoint<int16_t,1> b;
    b = a8;
    Assert(0x0002 == b.value_,"Assign 1");

    return true;
}

int main(void)
{

    TestFixedPoint();

    std::vector<FpComplex> x1(N);

    for( int test_signal_i = 0; test_signal_i < 3; test_signal_i++)
    {

        // Load the test signal
        for ( unsigned int i = 0; i < N; i++)
        {
            x1[i] = test_signals[test_signal_i][i];
        }

        Fft<FpComplex,N>::ditfft(x1.data(),N);

        Disp(x1, 1, 1);

        std:: cout << "Max Freq: " << 
            Fft<FpComplex,N>::maxFreq(x1.data()) << std::endl;
    }

} // end main

