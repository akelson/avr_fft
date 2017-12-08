#include <iostream>

#include "fft.hpp"

#include "twiddle_factors_64.cpp"

int main(void)
{
    double foo[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    Fft<double,64>::ditfft(foo,64);

    for (int i = 0; i < 16; i++)
    {
        std::cout << foo[i] << std::endl;
    }
} // end main
