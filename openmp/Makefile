# Apple's clang doesn't support OpenMP, so default to g++.
CC  = gcc
CXX = g++

CFLAGS   = -Wall -MMD
CXXFLAGS = -Wall -MMD -std=c++11

CFLAGS   += -fopenmp
CXXFLAGS += -fopenmp
LDFLAGS  += -fopenmp

src := $(wildcard *.c *.cc *.cpp)
src := $(filter-out Trace.cc, $(src))
exe := $(basename $(src))
dep := $(addsuffix .d, $(exe))

all: $(exe)

release: Trace.o

thread_local: thread_local.o thread_local_2.o

%: %.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	-rm -f $(exe) *.o *.d

-include $(dep)
