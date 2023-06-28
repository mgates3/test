CXX      = g++
CXXFLAGS = -fPIC -Wall -MMD -I src
LDFLAGS  = -fPIC

#HASHDEPS_DISABLE ?= true
include hashdeps.mk

src  = src/a.cc src/b.cc
obj  = ${addsuffix .o, ${basename ${src}}}
dep  = ${addsuffix .d, ${basename ${src}}}
hash = ${addsuffix .dephash, ${basename ${src}}}

test_src  = test/tester.cc
test_obj  = ${addsuffix .o, ${basename ${test_src}}}
test_dep  = ${addsuffix .d, ${basename ${test_src}}}
test_hash = ${addsuffix .dephash, ${basename ${test_src}}}

lib = lib/libmine.so
tester = test/tester

.DEFAULT_GOAL := all
.PHONY: all echo clean
.DELETE_ON_ERROR:
.SUFFIXES:

all: test/tester

echo:
	@echo "src                          =" ${src}
	@echo "hash_deps src                =" ${call hash_deps,${src}}
	@echo "unhash_deps( hash_deps src ) =" ${call unhash_deps,${call hash_deps,${src}}}

${tester}: ${test_obj} ${lib}
	${CXX} ${CXXFLAGS} -o $@ ${test_obj} -L lib -lmine

${lib}: ${obj}
	${CXX} ${LDFLAGS} -shared -o $@ ${obj}

%.o: ${call hash_deps,%.cc}
	${CXX} ${CXXFLAGS} -c -o $@ ${call unhash_deps,$<}
	@${call hash_deps_in_autogen_dep_file,${@:%.o=%.d}}

clean: hashdeps_clean
	-rm -f ${obj} ${dep} ${test_obj} ${test_dep} ${tester} ${lib}

-include ${dep}
-include ${test_dep}
