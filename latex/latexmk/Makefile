# Note: latexmk 4.63b, 17 March 2019, used in TexLive 2019,
# doesn't generate dependencies correctly.

docs = foo.pdf bar.pdf
base = ${basename ${docs}}

FLAGS = -pdf

all: ${docs}

%.pdf: %.tex
	latexmk -pdf -M -MF $*.d $*

clean:
	latexmk -c ${FLAGS}

cleanall: distclean

distclean:
	latexmk -C ${FLAGS}

-include *.d
