#!/usr/bin/python

import math
import cmath
import sys

def generate_twiddle_factors(N, type_name):
    with open("twiddle_factors_{}.cpp".format(N), "w") as f:
        f.write('#include "Fft.hpp"\n')
        f.write('#include "CommonTypes.hpp"\n')
        f.write("template<>\n")
        f.write("const {} Fft<{},{}>::twiddle_factors_[{}] = \n"
                .format(type_name, type_name, N, N))
        f.write("{\n")
        for k in range(N):
            if (k):
                f.write(",")
            if (k and not k % 1):
                f.write("\n")
            w = cmath.exp(complex(0,-2.0*math.pi*k/N))
            f.write("{{{: 1.10f},{: 1.10f}}}".format(w.real, w.imag))

        f.write("\n};\n")

if __name__ == "__main__":
    generate_twiddle_factors(int(sys.argv[1]), sys.argv[2]);
