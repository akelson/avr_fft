#!/usr/bin/python

import math
import sys

def generate_twiddle_factors(N):
    with open("twiddle_factors_{}.cpp".format(N), "w") as f:
        f.write("template<>\n")
        f.write("const int16_t Fft<FpComplex,{}>::twiddle_factors_[{}] = \n"
                .format(N,N))
        f.write("{\n")
        # TODO
        i = 1
        for k in range(N):
            w = int(0x7FFF * math.exp(-2*math.pi*i*k/N))
            if (k):
                f.write(",")
            if (k and not k % 4):
                f.write("\n")
            f.write("0x{:04X}".format(w))
        f.write("\n};\n")

if __name__ == "__main__":
    generate_twiddle_factors(int(sys.argv[1]));
