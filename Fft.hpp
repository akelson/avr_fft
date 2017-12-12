//------------------------------------------------------------------------------
// fft.hpp
//------------------------------------------------------------------------------

template<typename T>
T ConvertTwiddleFactor(const int16_t);

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

