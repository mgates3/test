-include make.inc

CXXFLAGS = -fPIC -Wall -MMD
LDFLAGS  = -fPIC

build ?= __build

# Define ${build_} as local copy of ${build}, and strip trailing / slash.
ifneq (${build},)
    build_ := ${patsubst %/,%,${build}}
else
    # If ${build} is empty, use . so ${build_}/foo becomes ./foo and not /foo.
    build_ := .
endif

incdir   ?= ${build_}/include
libdir   ?= ${build_}/lib

src       = ${wildcard src/*.cc}
obj       = ${addprefix ${build_}/, ${addsuffix .o, ${basename ${src}}}}
dep       = ${addprefix ${build_}/, ${addsuffix .d, ${basename ${src}}}}

test_src  = ${wildcard test/*.cc}
test_obj  = ${addprefix ${build_}/, ${addsuffix .o, ${basename ${test_src}}}}
dep      += ${addprefix ${build_}/, ${addsuffix .d, ${basename ${test_src}}}}

objdirs   = ${sort ${dir ${obj} ${test_obj}}}

tester    = ${build_}/test/tester

libblaspp = ${libdir}/libblaspp.so
ld_blaspp = -lblaspp

CXXFLAGS += -I include -I ${incdir}
LDFLAGS  += -L ${libdir} -Wl,-rpath,${abspath ${libdir}}

#-------------------------------------------------------------------------------
# auto-detect OS
# $OSTYPE may not be exported from the shell, so echo it
ostype := $(shell echo $${OSTYPE})
ifneq ($(findstring darwin, $(ostype)),)
    # MacOS is darwin
    macos = 1
endif

# MacOS needs shared library's path set
ifeq ($(macos),1)
    install_name = -install_name @rpath/$(notdir $@)
else
    install_name =
endif

#===============================================================================
# Rules
.PHONY: all test lib clean echo
.SUFFIXES:
.DELETE_ON_ERROR:

all: lib test

test: ${tester}

lib: ${libblaspp}

# Normally configure.py or CMake would create config header.
config := ${incdir}/blas_config.hh

${config}: | ${incdir}
	touch $@

# Create build directories.
# (Not lib, because lib -> libslate.so -> lib circular dependency.)
${incdir} ${objdirs}:
	mkdir -p $@

#-------------------------------------------------------------------------------
# Library and tester

# Link tester.
${tester}: ${test_obj} ${libblaspp} | ${objdirs}
	${CXX} ${LDFLAGS} ${LIBS} \
		-o $@ \
		${test_obj} \
		${ld_blaspp}

# Link library.
${libblaspp}: ${obj}
	mkdir -p ${libdir}
	${CXX} ${LDFLAGS} \
		-shared ${install_name} \
		-o $@ \
		${obj}

# Compile objects.
${build_}/%.o: %.cc ${config} | ${objdirs}
	${CXX} ${CXXFLAGS} -c -o $@ $<

clean:
	-rm -f ${tester} ${libblaspp} ${obj} ${test_obj} ${dep} ${incdir}/blas_config.hh

# Auto-generated dependencies.
-include ${dep}

#-------------------------------------------------------------------------------
# Debugging

echo:
	@echo "build     = '${build}'"
	@echo "build_    = '${build_}'"
	@echo "libdir    = '${libdir}'"
	@echo "incdir    = '${incdir}'"
	@echo "objdirs   = '${objdirs}'"
	@echo
	@echo "src       = '${src}'"
	@echo "obj       = '${obj}'"
	@echo "test_src  = '${test_src}'"
	@echo "test_obj  = '${test_obj}'"
	@echo "dep       = '${dep}'"
	@echo "libblaspp = '${libblaspp}'"
	@echo "tester    = '${tester}'"
