#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "Complex.hpp"
#include "FixedPoint.hpp"

#include "Fft.hpp"
#include "CommonTypes.hpp"

#include "test_signals.hpp"

int magnitude(FpComplex val)
{
  auto re = val.re_;
  auto im = val.im_;
  return (re*re + im*im).value_;
}

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

    // Output the index.
    PORTD = ~largest_index;
    _delay_ms(1000);

    test_signal_i++;
    if ( test_signal_i > 2)
    {
      test_signal_i = 0;
      Flash();
    }
  }
} // end main
