-include make.inc

src = ${wildcard *.cc}
obj = ${addsuffix .o, ${basename ${src}}}
exe = ${basename ${src}}

fsrc = ${wildcard *.f90}
fobj = ${addsuffix .o, ${basename ${fsrc}}}
fexe = ${basename ${fsrc}}

.SUFFIXES:
.SECONDARY:

all: ${exe} ${fexe}

${exe}: %: %.o
	${CXX} ${LDFLAGS} -o $@ $^ \
		${LIBS}

${fexe}: %: %.o
	${FC} ${LDFLAGS} -o $@ $^ \
		${LIBS}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $<

%.o: %.f90
	${FC} ${FCFLAGS} -c -o $@ $<

clean:
	-rm -f ${exe} ${fexe} *.o *.d
