# SLATE user asked about linking: it was compiling dynamic library,
# but failing to link with it, with an error like:
#     /usr/bin/ld: cannot find -lslate2
# Turns out this was on Cray and the compiler defaulted to static linking.
# Normally:
# make test/tester should work.
# make test/tester-static should fail with error that it cannot find libraries:
#
# saturn> g++ -static -o test/tester-static test/tester.o -Llib -lslate
# /usr/bin/ld: cannot find -lslate
# /usr/bin/ld: cannot find -lm
# /usr/bin/ld: cannot find -lc
# collect2: error: ld returned 1 exit status
#
# thyme> g++ -static -o test/tester-static test/tester.o -Llib -lslate
# ld: library not found for -lcrt0.o
#
# because only the shared library exists:
# thyme> ls lib/
# libslate.so*

CXX      = g++
CXXFLAGS = -Wall -fPIC
LDFLAGS  = -fPIC

all:
	$(MAKE) test/tester
	$(MAKE) test/tester-static

test/tester: test/tester.o lib/libslate.so
	$(CXX) -o $@ test/tester.o -Llib -lslate

test/tester-static: test/tester.o lib/libslate.so
	$(CXX) -static -o $@ test/tester.o -Llib -lslate

lib/libslate.so: src/foo.o
	$(CXX) $(LDFLAGS) -shared -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f */*.o test/tester lib/*.a lib/*.so
