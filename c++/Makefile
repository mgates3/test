-include make.inc

CFLAGS   += -MMD
CXXFLAGS += -MMD -fopenmp
LDFLAGS  +=      -fopenmp

src = ${wildcard *.cc} ${wildcard *.c}
obj = ${addsuffix .o, ${basename ${src}}}
dep = ${addsuffix .d, ${basename ${src}}}
exe = ${basename ${src}}

exe := ${filter-out norm_impl template_b, ${exe}}
norm: norm.o norm_impl.o
elpa_main: elpa_wrapper.o
unordered_map: fasthash.o

template_a: template_b.o

ifeq (${error},1)
    CXXFLAGS += -DERROR
endif

.SUFFIXES:
.SECONDARY:
.DEFAULT_TARGET: all

all: ${exe}

%: %.o
	${CXX} ${LDFLAGS} -o $@ $^ \
		${LIBS}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $<

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

%.i: %.cc
	${CXX} ${CXXFLAGS} -E -o $@ $<

clean:
	-rm -f ${exe} *.o *.d

-include ${dep}

echo:
	@echo "src = ${src}"
	@echo
	@echo "obj = ${obj}"
	@echo
	@echo "dep = ${dep}"
	@echo
	@echo "exe = ${exe}"
	@echo
