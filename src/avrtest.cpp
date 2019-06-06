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

<<<<<<< HEAD:src/avrtest.cpp
=======
int magnitude(FpComplex val)
{
  auto re = val.re_;
  auto im = val.im_;
  return (re*re + im*im).value_;
}
>>>>>>> de51e6e633280e351d14ce4841af6370f4493a79:avrtest.cpp

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

  const FpComplex* test_signals[] =
  {
    test_signal_5Hz,
    test_signal_8Hz,
    test_signal_16Hz,
  };

  FpComplex x1[N] = {};

  int test_signal_i = 0;

<<<<<<< HEAD:src/avrtest.cpp
    FpComplex x1[N] = {};
=======
  while (1)
  {
    PORTD = 0xFF;

    // Load the test signal
    for ( unsigned int i = 0; i < N; i++)
    {
      x1[i] = test_signals[test_signal_i][i];
    }

    Fft<FpComplex,N>::ditfft(x1,N);

    // Find largest component.
    int largest_value = 0;
    char largest_index = 0;
    for ( unsigned int i = 0; i < N; i++)
    {
      int mag = magnitude(x1[i]);
      if ( mag > largest_value )
      {
        largest_value = mag;
        largest_index = i;
      }
    }
>>>>>>> de51e6e633280e351d14ce4841af6370f4493a79:avrtest.cpp

    // Output the index.
    PORTD = ~largest_index;
    _delay_ms(1000);

    test_signal_i++;
    if ( test_signal_i > 2)
    {
<<<<<<< HEAD:src/avrtest.cpp
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
=======
      test_signal_i = 0;
      Flash();
>>>>>>> de51e6e633280e351d14ce4841af6370f4493a79:avrtest.cpp
    }
  }
} // end main
