#!/usr/bin/python

import math
import sys

def generate_twiddle_factors(N):
    with open("twiddle_factors_{}.cpp".format(N), "w") as f:
        f.write("template<>\n")
        f.write("const double Fft<double,{}>::twiddle_factors_[{}] = \n"
                .format(N,N))
        f.write("{\n")
        # TODO
        i = 1
        for k in range(N):
            w = math.exp(-2*math.pi*i*k/N)
            if (k):
                f.write(",")
            if (k and not k % 4):
                f.write("\n")
            f.write("{}".format(w))
        f.write("\n};\n")

if __name__ == "__main__":
    generate_twiddle_factors(int(sys.argv[1]));
