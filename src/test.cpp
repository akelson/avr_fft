#include <math.h>

#include <iostream>
#include <iomanip>
#include <complex>
#include <cstdint>
#include <vector>

#include "Complex.hpp"

#include "Fft.hpp"
#include "CommonTypes.hpp"

#include "test_signals.hpp"

template<>
const FpComplex Fft<FpComplex,64>::twiddle_factors_[64];

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

void Print(const std::vector<FpComplex>& x)
{
  for (auto& item : x)
  {
    std::cout << item << std::endl;
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

    //Disp(x1, 1, 1);
    Print(x1);

    std:: cout << "Max Freq: " << 
      Fft<FpComplex,N>::maxFreq(x1.data()) << std::endl;
  }

  //x1[0] = FpComplex(1.0);
  ////AddSignal(x1, 8);
  ////AddSignal(x1, 1, 8, 0);
  ////AddSignal(x1, 1, 16, 0);
  ////AddSignal(x1, .5, 30, 0);
  ////AddSignal(x1, 5, 3);

  ////Disp(x1,5,10);
  //std::cout << std::endl;

  //for (int i = 0; i < N; i++)
  //{
  //  std::cout << x1[i] << std::endl;
  //}
  //std::cout << std::endl;

  ////Fft<FpComplex,N>::PrintTwiddleFactors();

  //Fft<FpComplex,N>::ditfft(x1.data(),N);
  ////Fft<FpComplex,N>::ditfft(x1.data(),N);

  ////Disp(x1,1,0);

  //for (int i = 0; i < x1.size()/2; i++)
  //{
  //  std::cout << x1[i] << std::endl;
  //}

} // end main

