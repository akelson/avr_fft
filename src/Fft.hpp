//------------------------------------------------------------------------------
// fft.hpp
//------------------------------------------------------------------------------

template<typename T>
T ConvertTwiddleFactor(const int16_t);

// TODO:
template<typename T>
int32_t magnitude(Complex<T> value)
{
    return (value.re_*value.re_ + value.im_*value.im_).value_;
    int32_t mag = value.re_.value_;
    if ( mag > 0 )
    {
        return mag;
    }
    else
    {
        return -mag;
    }
}

template<typename T, size_t N>
class Fft
{
public:

    // Decimation-in-time FFT
    static void ditfft(T * const X, const size_t n)
    {
        if ( n >= 2 )
        {
            separate(X,n);
            ditfft(X,    n/2);
            ditfft(X+n/2,n/2);
        }
        else
        {
            return;
        }

        for (size_t k = 0; k < n/2; k++)
        {
            const T twiddle_factor = twiddle_factors_[k * (N/n)];
            const T e = X[k];
            const T o_exp = X[k+n/2] * twiddle_factor;
            X[k] =     e + o_exp;
            X[n/2+k] = e - o_exp;
        } // end for
    } // end ditfft

    static int16_t maxFreq(T * const X)
    {
        // Find largest component.
        int32_t largest_value = 0;
        int16_t largest_index = 0;
        for ( int16_t i = 0; i < int16_t(N/2); i++)
        {
            int32_t mag = magnitude(X[i]);
            if ( mag > largest_value )
            {
                largest_value = mag;
                largest_index = i;
            }
        }
        return largest_index;
    }

    static void separate(T * const x, const size_t n)
    {
        static T odds[N/2];

        for (size_t i = 0; i < n/2; i++)
        {
            x[i] = x[i*2];
            odds[i] = x[i*2+1];
        }

        for (size_t i = 0; i < n/2; i++)
        {
            x[n/2+i] = odds[i];
        }
    } // separate


    static const T twiddle_factors_[N];

}; // Fft



