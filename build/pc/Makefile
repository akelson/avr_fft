SRC_DIR = ../../src
AUTOGEN_SRC_DIR = $(SRC_DIR)/autogen

TARGET = test

AUTOGEN_TWIDDLE = ../../autogen_twiddle_factors.py
AUTOGEN_TEST_SIGNAL = ../../autogen_test_signal.py

RADIX = 8
CMPLX_TYPE = FpComplex
TWIDDLE_SRC = $(AUTOGEN_SRC_DIR)/twiddle_factors_$(RADIX).cpp
TEST_SIGNAL_SRC = $(AUTOGEN_SRC_DIR)/test_signal_$(RADIX).cpp

SRCS = $(TARGET).cpp $(TWIDDLE_SRC) $(TEST_SIGNAL_SRC)

DEP = $(OBJ:%.o=%.d)

VPATH = ../../src

INC = -I$(SRC_DIR)

CXXFLAGS = -g -Wall -std=c++11 -Os $(INC)
CXX = g++
CC = $(CXX)

$(TARGET): $(TARGET).o

$(TARGET).o: $(SRCS)

$(TWIDDLE_SRC): $(AUTOGEN_TWIDDLE)
	cd $(AUTOGEN_SRC_DIR); \
	$(AUTOGEN_TWIDDLE) $(RADIX) $(CMPLX_TYPE)

$(TEST_SIGNAL_SRC): $(AUTOGEN_TEST_SIGNAL)
	cd $(AUTOGEN_SRC_DIR); \
	$(AUTOGEN_TEST_SIGNAL) $(RADIX) $(CMPLX_TYPE)

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f $(OBJ)
	rm -f $(AUTOGEN_SRC_DIR)/*

