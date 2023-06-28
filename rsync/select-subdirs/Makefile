# Trying to backup, say:
# 	Library/jEdit/
#	Library/Application Support/Firefox/Profiles/xyz/bookmarks*
# while excluding everything else in Library.

# https://www.linuxquestions.org/questions/linux-software-2/rsync-include-exclude-problems-636504/
# https://stackoverflow.com/questions/8270519/rsync-exclude-a-directory-but-include-a-subdirectory

bar = "----------------------------------------------------------------------"

all: dst-0 dst-1 dst-2 dst-3

.NOTPARALLEL:

dst-0:
	@echo "${bar} $@"
	@echo "# Copy everything."
	rsync -avn src $@

dst-1:
	@echo "${bar} $@"
	@echo "# Copy 2/D.html but not 2/E/X"
	rsync -avn --include 2/D.html --include 2/E/X --exclude '2/*' src $@

dst-2:
	@echo "${bar} $@"
	@echo "# Same as dst-1, using a filter file"
	rsync -avn --exclude-from filter2.txt src $@

dst-3:
	@echo "${bar} $@"
	@echo "# Copy 2/D.html and 2/E/X"
	rsync -avn --exclude-from filter3.txt src $@
