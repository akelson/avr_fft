SRC_DIR = ../../src
AUTOGEN_SRC_DIR = $(SRC_DIR)/autogen

TARGET = avrtest

AUTOGEN_TWIDDLE = ../../autogen_twiddle_factors.py
AUTOGEN_TEST_SIGNAL = ../../autogen_test_signal.py

RADIX = 64
CMPLX_TYPE = FpComplex
TWIDDLE_SRC = $(AUTOGEN_SRC_DIR)/twiddle_factors_$(RADIX).cpp
TEST_SIGNAL_SRC = $(AUTOGEN_SRC_DIR)/test_signal_$(RADIX).cpp

SRCS = $(TARGET).cpp $(TWIDDLE_SRC) $(TEST_SIGNAL_SRC)

DEP = $(OBJ:%.o=%.d)

VPATH = ../../src

MCU = atmega328
PROGRAMMER = stk500
F_CPU = 1000000UL

INC = -I$(SRC_DIR)

AVRFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DAVR
CXXFLAGS = $(AVRFLAGS) -g -Wall -std=c++11 -Os $(INC)
CXX = avr-c++
CC = $(CXX)

$(TARGET).hex: $(TARGET)
	avr-objcopy -j .text -j .data -O ihex $(TARGET) $(TARGET).hex

$(TARGET): $(SRCS) 
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/$(TARGET).cpp -o $(TARGET)

$(TWIDDLE_SRC): $(AUTOGEN_TWIDDLE)
	cd $(AUTOGEN_SRC_DIR); \
	$(AUTOGEN_TWIDDLE) $(RADIX) $(CMPLX_TYPE)

$(TEST_SIGNAL_SRC): $(AUTOGEN_TEST_SIGNAL)
	cd $(AUTOGEN_SRC_DIR); \
	$(AUTOGEN_TEST_SIGNAL) $(RADIX) $(CMPLX_TYPE)

.PHONY: prog
prog: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -P /dev/cu.usbserial -p $(MCU) -U flash:w:$(TARGET).hex

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f $(OBJ)
	rm -f $(AUTOGEN_SRC_DIR)/*
