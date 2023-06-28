CF = clang-format

style  = IndentWidth: 4,
style += AllowShortBlocksOnASingleLine: false,
style += AllowShortFunctionsOnASingleLine: false,
style += IndentCaseLabels: true,
style += FixNamespaceComments: true

default: all

#-------------------------------------------------------------------------------
Braces = \
    Braces-Attach.cc \
    Braces-Linux.cc \
    Braces-Mozilla.cc \
    Braces-Stroustrup.cc \
    Braces-Allman.cc \
    Braces-GNU.cc \
    Braces-WebKit.cc \

# Clang 10
# Braces-Whitesmiths.cc

all += ${Braces}

Braces-Attach.cc: Braces.cc
	${CF} -style="{ BreakBeforeBraces: Attach, ${style} }" $< > $@

Braces-Linux.cc: Braces.cc
	${CF} -style="{ BreakBeforeBraces: Linux, ${style} }" $< > $@

Braces-Mozilla.cc: Braces.cc
	${CF} -style="{ BreakBeforeBraces: Mozilla, ${style} }" $< > $@

Braces-Stroustrup.cc: Braces.cc
	${CF} -style="{ BreakBeforeBraces: Stroustrup, ${style} }" $< > $@

Braces-Allman.cc: Braces.cc
	${CF} -style="{ BreakBeforeBraces: Allman, ${style} }" $< > $@

#Braces-Whitesmiths.cc: Braces.cc
#	${CF} -style="{ BreakBeforeBraces: Whitesmiths, ${style} }" $< > $@

Braces-GNU.cc: Braces.cc
	${CF} -style="{ BreakBeforeBraces: GNU, ${style} }" $< > $@

Braces-WebKit.cc: Braces.cc
	${CF} -style="{ BreakBeforeBraces: WebKit, ${style} }" $< > $@

#-------------------------------------------------------------------------------
Access = \
	Access-4.cc \
	Access-0.cc

all += ${Access}

Access-4.cc: Access.cc
	${CF} -style="{ AccessModifierOffset: -4, ${style} }" $< > $@

Access-0.cc: Access.cc
	${CF} -style="{ AccessModifierOffset: 0, ${style} }" $< > $@

#-------------------------------------------------------------------------------
OpenBracket = \
	OpenBracket-Align.cc \
	OpenBracket-DontAlign.cc \
	OpenBracket-AlwaysBreak.cc

all += ${OpenBracket}

OpenBracket-Align.cc: OpenBracket.cc
	${CF} -style="{ AlignAfterOpenBracket: Align, ${style} }" $< > $@

OpenBracket-DontAlign.cc: OpenBracket.cc
	${CF} -style="{ AlignAfterOpenBracket: DontAlign, ${style} }" $< > $@

OpenBracket-AlwaysBreak.cc: OpenBracket.cc
	${CF} -style="{ AlignAfterOpenBracket: AlwaysBreak, ${style} }" $< > $@

#-------------------------------------------------------------------------------
Assignments = \
	Assignments-0.cc \
	Assignments-1.cc

all += ${Assignments}

Assignments-0.cc: Assignments.cc
	${CF} -style="{ AlignConsecutiveAssignments: false, ${style} }" $< > $@

Assignments-1.cc: Assignments.cc
	${CF} -style="{ AlignConsecutiveAssignments: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
Declarations = \
	Declarations-0.cc \
	Declarations-1.cc \
	Declarations-both.cc

all += ${Declarations}

Declarations-0.cc: Declarations.cc
	${CF} -style="{ AlignConsecutiveDeclarations: false, ${style} }" $< > $@

Declarations-1.cc: Declarations.cc
	${CF} -style="{ AlignConsecutiveDeclarations: true, ${style} }" $< > $@

Declarations-both.cc: Declarations.cc
	${CF} -style="{ AlignConsecutiveDeclarations: true, AlignConsecutiveAssignments: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
EscapedNewlines = \
	EscapedNewlines-DontAlign.cc \
	EscapedNewlines-Left.cc \
	EscapedNewlines-Right.cc

all += ${EscapedNewlines}

EscapedNewlines-DontAlign.cc: EscapedNewlines.cc
	${CF} -style="{ AlignEscapedNewlines: DontAlign, ${style} }" $< > $@

EscapedNewlines-Left.cc: EscapedNewlines.cc
	${CF} -style="{ AlignEscapedNewlines: Left, ${style} }" $< > $@

EscapedNewlines-Right.cc: EscapedNewlines.cc
	${CF} -style="{ AlignEscapedNewlines: Right, ${style} }" $< > $@

#-------------------------------------------------------------------------------
Operands = \
	Operands-0.cc \
	Operands-1.cc

all += ${Operands}

Operands-0.cc: Operands.cc
	${CF} -style="{ AlignOperands: false, ${style} }" $< > $@

Operands-1.cc: Operands.cc
	${CF} -style="{ AlignOperands: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
TrailingComments = \
	TrailingComments-0.cc \
	TrailingComments-1.cc

all += ${TrailingComments}

TrailingComments-0.cc: TrailingComments.cc
	${CF} -style="{ AlignTrailingComments: false, ${style} }" $< > $@

TrailingComments-1.cc: TrailingComments.cc
	${CF} -style="{ AlignTrailingComments: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
ArgsNextLine = \
	ArgsNextLine-0-bin0.cc \
	ArgsNextLine-0-bin1.cc \
	ArgsNextLine-1-bin0.cc \
	ArgsNextLine-1-bin1.cc

all += ${ArgsNextLine}

ArgsNextLine-0-bin0.cc: ArgsNextLine.cc
	${CF} -style="{ AllowAllArgumentsOnNextLine: false, BinPackArguments: false, ${style} }" $< > $@

ArgsNextLine-0-bin1.cc: ArgsNextLine.cc
	${CF} -style="{ AllowAllArgumentsOnNextLine: false, BinPackArguments: true, ${style} }" $< > $@

ArgsNextLine-1-bin0.cc: ArgsNextLine.cc
	${CF} -style="{ AllowAllArgumentsOnNextLine: true, BinPackArguments: false, ${style} }" $< > $@

ArgsNextLine-1-bin1.cc: ArgsNextLine.cc
	${CF} -style="{ AllowAllArgumentsOnNextLine: true, BinPackArguments: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
Constructor = \
	Constructor-0.cc \
	Constructor-1.cc

all += ${Constructor}

Constructor-0.cc: Constructor.cc
	${CF} -style="{ AllowAllConstructorInitializersOnNextLine: false, ConstructorInitializerAllOnOneLineOrOnePerLine: true, ${style} }" $< > $@

Constructor-1.cc: Constructor.cc
	${CF} -style="{ AllowAllConstructorInitializersOnNextLine: true, ConstructorInitializerAllOnOneLineOrOnePerLine: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
Params = \
	Params-0.cc \
	Params-1.cc

all += ${Params}

Params-0.cc: Params.cc
	${CF} -style="{ AllowAllParametersOfDeclarationOnNextLine: false, BinPackParameters: false, ${style} }" $< > $@

Params-1.cc: Params.cc
	${CF} -style="{ AllowAllParametersOfDeclarationOnNextLine: true, BinPackParameters: false, ${style} }" $< > $@

#-------------------------------------------------------------------------------
ShortCase = \
	ShortCase-0.cc \
	ShortCase-1.cc

all += ${ShortCase}

ShortCase-0.cc: ShortCase.cc
	${CF} -style="{ AllowShortCaseLabelsOnASingleLine: false, ${style} }" $< > $@

ShortCase-1.cc: ShortCase.cc
	${CF} -style="{ AllowShortCaseLabelsOnASingleLine: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
ShortFunc = \
	ShortFunc-None.cc \
	ShortFunc-InlineOnly.cc \
	ShortFunc-Empty.cc \
	ShortFunc-All.cc

all += ${ShortFunc}

ShortFunc-None.cc: ShortFunc.cc
	${CF} -style="{ AllowShortFunctionsOnASingleLine: None, ${style} }" $< > $@

ShortFunc-InlineOnly.cc: ShortFunc.cc
	${CF} -style="{ AllowShortFunctionsOnASingleLine: InlineOnly, ${style} }" $< > $@

ShortFunc-Empty.cc: ShortFunc.cc
	${CF} -style="{ AllowShortFunctionsOnASingleLine: Empty, ${style} }" $< > $@

ShortFunc-All.cc: ShortFunc.cc
	${CF} -style="{ AllowShortFunctionsOnASingleLine: All, AllowShortBlocksOnASingleLine: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
ShortIf = \
	ShortIf-Never.cc \
	ShortIf-WithoutElse.cc \
	ShortIf-Always.cc

all += ${ShortIf}

ShortIf-Never.cc: ShortIf.cc
	${CF} -style="{ AllowShortIfStatementsOnASingleLine: Never, ${style} }" $< > $@

ShortIf-WithoutElse.cc: ShortIf.cc
	${CF} -style="{ AllowShortIfStatementsOnASingleLine: WithoutElse, ${style} }" $< > $@

ShortIf-Always.cc: ShortIf.cc
	${CF} -style="{ AllowShortIfStatementsOnASingleLine: Always, AllowShortBlocksOnASingleLine: true, ${style} }" $< > $@

#-------------------------------------------------------------------------------
preproc-out.cc: preproc.cc
	cp $< $@
	sed -i 's/#pragma omp/\/\/#pragma omp/' $@
	${CF} -i -style="{ ${style} }" $@
	sed -i 's/\/\/#pragma omp/#pragma omp/' $@

#-------------------------------------------------------------------------------
pragma-out.cc: pragma.cc
	cp $< $@
	sed -i 's/#pragma omp/\/\/#pragma omp/' $@
	${CF} -i -style="{ ${style} }" $@
	sed -i 's/\/\/#pragma omp/#pragma omp/' $@

#-------------------------------------------------------------------------------
all: ${all}

echo:
	@echo "all ${all}"

clean:
	-rm -f ${all}

.DELETE_ON_ERROR:
