# Demonstrates that %.hip.cc can be treated differently than %.cc
# However, the order matters: hip has to be first. Here, %.toe.cc is
# treated like %.cc because it is after %.o
#
# thyme makefile/hip> make
# cc -c -o foo.o foo.cc
# hipcc -c -o bar.hip.o bar.hip.cc
# cc -c -o zab.toe.o zab.toe.cc
# cc -o exe foo.o bar.hip.o zab.toe.o

exe: foo.o bar.hip.o zab.toe.o

.SUFFIXES:

# Before %.o: %.cc rule!
%.hip.o: %.hip.cc
	@echo "hipcc -c -o $@ $<"
	@touch $@

%.o: %.cc
	@echo "cc -c -o $@ $<"
	@touch $@

# Unused because it's after %.o: %.cc rule!
%.toe.o: %.toe.cc
	@echo "toecc -c -o $@ $<"
	@touch $@

exe:
	@echo "cc -o $@ $^"
	@touch $@

clean:
	-rm -f exe *.o
