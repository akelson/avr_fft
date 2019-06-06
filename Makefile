MCU = atmega328
PROGRAMMER = stk500
F_CPU = 1000000UL

AVRFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -DAVR
CFLAGS = $(AVRFLAGS) -g -Wall
#CXXFLAGS = $(CFLAGS) -g -Wall -std=c++11 -stdlib=libc++ -O0
CXXFLAGS = -g -Wall -std=c++11
CXX = g++
AVRCXX = avr-c++

REMOVE = rm -f

TARGET = avrtest

TEST_TARGET = test

$(TARGET).hex: $(TARGET)
	avr-objcopy -j .text -j .data -O ihex $(TARGET) $(TARGET).hex

$(TARGET): $(TARGET).cpp Fft.hpp Complex.hpp FixedPoint.hpp \
	twiddle_factors_64.cpp test_signal_64.cpp
	$(AVRCXX) $(AVRFLAGS) $(CXXFLAGS) $(TARGET).cpp -o $(TARGET)

$(TEST_TARGET): $(TEST_TARGET).cpp Fft.hpp Complex.hpp FixedPoint.hpp \
	twiddle_factors_64.cpp test_signal_64.cpp
	$(CXX) $(CXXFLAGS) $(TEST_TARGET).cpp -o $(TEST_TARGET)

twiddle_factors_64.cpp: autogen_twiddle_factors.py
	./autogen_twiddle_factors.py 64 FpComplex

test_signal_64.cpp: autogen_test_signal.py
	./autogen_test_signal.py 64 FpComplex

.PHONY: prog
prog: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -P /dev/cu.usbserial -p $(MCU) -U flash:w:$(TARGET).hex

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -rf $(TARGET).dSYM
	rm -f twiddle_factors_*.cpp
	rm -f test_signal*.cpp
	rm -f *.o
	rm -f *.hex
