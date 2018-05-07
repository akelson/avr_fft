#!/usr/bin/python

import math
import cmath
import sys

def generate_signal(N, type_name, freq):
    with open("test_signal_{}.cpp".format(N), "a") as f:
        f.write("const {} test_signal_{}Hz[{}] = \n"
                .format(type_name, freq, N))
        f.write("{\n")
        for k in range(N):
            if (k):
                f.write(",")
            if (k and not k % 1):
                f.write("\n")
            sig = 0.1*math.cos(2 * math.pi * k * freq / N)
            f.write("{{{: 1.10f},{: 1.10f}}}".format(sig,0))

        f.write("\n};\n")

if __name__ == "__main__":
    with open("test_signal_{}.cpp".format(sys.argv[1]), "w") as f:
        pass
    generate_signal(int(sys.argv[1]), sys.argv[2],int(1));
    generate_signal(int(sys.argv[1]), sys.argv[2],int(15));
    generate_signal(int(sys.argv[1]), sys.argv[2],int(3));

    with open("test_signal_{}.cpp".format(sys.argv[1]), "a") as f:
        f.write(
        """
        const FpComplex* test_signals[] =
        {
            test_signal_1Hz,
            test_signal_15Hz,
            test_signal_3Hz,
            //test_signal_7Hz,
        };""")
