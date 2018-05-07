#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "Complex.hpp"
#include "FixedPoint.hpp"

#include "Fft.hpp"


static const size_t N = 64;

using Fp = FixedPoint<int16_t, 8>;
using FpComplex = Complex<Fp>;

#include "autogen/twiddle_factors_64.cpp"
#include "autogen/test_signal_64.cpp"


void Flash()
{
    for (int i = 0; i < 0xFF; i++)
    {
        PORTD = i;
		_delay_ms(1);
    }
}

int main(void)
{
	DDRD = 0xFF;

    Flash();

    FpComplex x1[N] = {};

    int test_signal_i = 0;

    while (1)
    {
		PORTD = 0xFF;

        // Load the test signal
        for ( unsigned int i = 0; i < N; i++)
        {
            x1[i] = test_signals[test_signal_i][i];
        }

        Fft<FpComplex,N>::ditfft(x1,N);

        // Output the index.
		PORTD = ~(Fft<FpComplex,N>::maxFreq(x1));
		_delay_ms(1000);

        test_signal_i++;
        if ( test_signal_i > 2)
        {
            test_signal_i = 0;
            Flash();
        }
    }
} // end main
