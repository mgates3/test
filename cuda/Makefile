-include make.inc

# If CUDA_PATH isn't set, use CUDA_HOME.
# If still empty, infer from location of nvcc.
CUDA_PATH ?= ${CUDA_HOME}
ifeq (${CUDA_PATH},)
    nvcc_path := $(shell which $(NVCC) 2>/dev/null)
    CUDA_PATH := $(call dir_strip, $(call dir_strip, $(nvcc_path)))
endif

# Add CUDA include and lib directories.
ifneq (${CUDA_PATH},)
    CXXFLAGS += -I ${CUDA_PATH}/include
    ifneq (${wildcard ${CUDA_PATH}/lib64},)
        LDFLAGS += -L ${CUDA_PATH}/lib64
    else
        LDFLAGS += -L ${CUDA_PATH}/lib
    endif
endif

NVCCFLAGS += -Xcompiler -Wno-unused-function
LIBS += -lcudart -lcublas

src  = ${wildcard *.cu}
src += ${wildcard *.cc}
obj  = ${addsuffix .o, ${basename ${src}}}
exe  = ${basename ${src}}

.SUFFIXES:
.SECONDARY:

all: ${exe}

%: %.o
	${CXX} ${LDFLAGS} -o $@ $^ \
		${LIBS}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $<

%.o: %.cu
	${NVCC} ${NVCCFLAGS} -c -o $@ $<

%.i: %.cu
	${NVCC} ${NVCCFLAGS} -E -o $@ $<

clean:
	-rm -f ${exe} *.o *.d
