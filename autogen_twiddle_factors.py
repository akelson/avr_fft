#!/usr/bin/python

import math
import cmath
import sys

def generate_twiddle_factors(N):
    with open("twiddle_factors_{}.cpp".format(N), "w") as f:
        f.write("template<>\n")
        f.write("const FpComplex Fft<FpComplex,{}>::twiddle_factors_[{}] = \n"
                .format(N,N))
        f.write("{\n")
        for k in range(N):
            w = cmath.exp(complex(0,-2*math.pi*k/N))
            if (k):
                f.write(",")
            if (k and not k % 4):
                f.write("\n")

            shift = (16 - 10);
            w_re = 0xFFFF & int(w.real * (0xFFFF >> shift));
            w_im = 0xFFFF & int(w.imag * (0xFFFF >> shift));
            f.write("{{0x{:04X},0x{:04X}}}".format(w_re, w_im))

        f.write("\n};\n")

if __name__ == "__main__":
    generate_twiddle_factors(int(sys.argv[1]));
