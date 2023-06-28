# Demonstrates how `make` leaves whitespace after the variable,
# and how to deal with it.
one      = 1
space    = 1
comment  = 1  # comment
strip1   = 1  # comment
strip2   = 1  # comment
zero     = 0
empty    =
# unset is, obviously, not set

# strip sets the value, so ?= must be done before strip.
#unset2 ?= unset2
unset2 := $(strip $(unset2))
unset2 ?= "unset2"

CXX := $(strip $(CXX))

# strip2 = $(strip $(strip2))  # error, recursive
strip2 := $(strip $(strip2))

#--------------------
ifeq ($(one),1)
    OK += one
else
    FAIL += no_one
endif

#--------------------
ifeq ($(one),none)
    $(error "one = none")
else
    $(error "one != none")
endif

#--------------------
ifeq ($(space),1)
    OK += space
else
    FAIL += no_space
endif

#--------------------
ifeq ($(comment),1)
    OK += comment
else
    FAIL += no_comment
endif

#--------------------
ifeq ($(strip $(strip1)),1)
    OK += strip1
else
    FAIL += no_strip1
endif

#--------------------
ifeq ($(strip2),1)
    OK += strip2
else
    FAIL += no_strip2
endif

#--------------------
ifeq ($(zero),1)
    OK += zero
else
    FAIL += no_zero
endif

#--------------------
ifeq ($(empty),1)
    OK += empty
else
    FAIL += no_empty
endif

#--------------------
ifeq ($(unset),1)
    OK += unset
else
    FAIL += no_unset
endif

#--------------------
is_mpi = $(filter mpi%,$(CXX))
ifneq ($(is_mpi),)
    mpi = 1
endif

#--------------------
echo:
	@echo "OK       ${OK}"
	@echo "FAIL     ${FAIL}"
	@echo "CXX      <$(CXX)>"
	@echo "one      <${one}>"
	@echo "space    <${space}>"
	@echo "comment  <${comment}>"
	@echo "strip1   <${strip1}>"
	@echo "strip2   <${strip2}>"
	@echo "zero     <${zero}>"
	@echo "empty    <${empty}>"
	@echo "unset    <${unset}>"
	@echo "unset2   <${unset2}>"
	@echo "mpi      <${mpi}>"
	@echo "is_mpi   <${is_mpi}>"
