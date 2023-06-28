# Tests whether sub-make inherits variables.
# Turns out, you need to either export them or pass them explicitly.
#
# 'exported' is defined in sub-make, even if it isn't defined here,
#
# 'not_exported' is not defined in sub-make, even if it is defined here,
# /unless/ it was exported from the original environment:
#     export not_exported=1; make
# or defined on the command line:
#     make not_exported=1
#
# 'cond_exported' is defined in sub-make iff it is defined here.
#

-include make.inc

export CXX exported

ifeq ($(cond_exported),1)
    export cond_exported
endif

# $(not_exported) is, obviously, not exported.

.PHONY: blaspp

# using export
blaspp:
	cd blaspp && $(MAKE)

# manually
blaspp2:
	cd blaspp && $(MAKE) CXX=$(CXX)
