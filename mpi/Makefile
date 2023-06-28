SHELL = /bin/bash

-include make.inc

src = ${wildcard *.cc}
obj = ${addsuffix .o, ${basename ${src}}}
exe = ${basename ${src}}

.SUFFIXES:
.SECONDARY:

all: ${exe}

%: %.o
	${CXX} ${LDFLAGS} -o $@ $^ \
		${LIBS}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $<

%.i: %.cc
	${CXX} ${CXXFLAGS} -E -o $@ $<

clean:
	-rm -f ${exe} *.o *.d

demo: ${exe}
	@for x in ${exe}; do \
	    echo "------------------------------------------------------------"; \
	    echo "mpirun -np 3 $$x"; \
	    mpirun -np 3 $$x; \
	done

echo:
	@echo "src = ${src}"
	@echo "obj = ${obj}"
	@echo "exe = ${exe}"
