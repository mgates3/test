# Demonstrates setting a C preprocessor macro to the hg id,
# and shows that `make` executes the shell only when compiling test.o,
# not when compiling app.o or anything else.
#
# thyme c++/hg-id> make test
# flubber
# c++ -DHG_ID='"15d93f9e8696+"' -c -o test.o test.cc
# c++  -o test test.o
# thyme c++/hg-id> make app
# c++  -c -o app.o app.cc
# c++  -o app app.o

all: test app

app: app.o
	${CXX} ${LDFLAGS} -o $@ $^

clean:
	-rm -f test app *.o

# To see when shell is invoked, print "flubber" to stderr.
test.o: CXXFLAGS += -DHG_ID='"${shell hg id -i; echo flubber 1>&2}"'
#test.o: CXXFLAGS += -DHG_ID='"${shell hg id -i}"'

test: test.o
	${CXX} ${LDFLAGS} -o $@ $^

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $<
