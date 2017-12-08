CXXFLAGS = -Wall -std=c++11 -stdlib=libc++ -O0
CXX = clang++

REMOVE = rm -f

TARGET = test

$(TARGET): $(TARGET).cpp fft.hpp twiddle_factors_64.cpp
	$(CXX) $(CXXFLAGS) $(TARGET).cpp -o $(TARGET)

twiddle_factors_64.cpp: autogen_twiddle_factors.py
	./autogen_twiddle_factors.py 64

.PHONY: clean
clean:
	rm $(TARGET)
	rm twiddle_factors_*.cpp
	rm *.o
