# Tests CMake string functions
# https://cmake.org/cmake/help/latest/command/string.html

cmake_minimum_required( VERSION 3.0 )

project( Test )

set( foo "FOO" )
set( bar "BAR" )
set( zab "zab" )
set( input "${foo}${bar}${foo}${baz}" )

message("
--------------------------------------------------------------------------------
quotes
")

# Generates list of 4 items aza, ${foo}, \t, bar.
set( msg  aza ${foo} \t bar  )
message( "<${msg}>\n" )

# Generates string.
set( msg " aza ${foo} \t bar " )
message( "<${msg}>\n" )

# Generates raw string w/o substitutions.
set( msg [[ aza ${foo} \t bar ]] )
message( "<${msg}>\n" )

# Any number of = between [[ and ]]
set( msg [=[ aza ${foo} \t bar ]=] )
message( "<${msg}>\n" )

set( msg [===[ aza ${foo} \t bar ]===] )
message( "<${msg}>\n" )

set( msg "multiline
string")
message( "<${msg}>\n" )

set( msg "
multiline
string
")
message( "<${msg}>\n" )

set( msg [[multiline
string]])
message( "<${msg}>\n" )

# Ignores beginning \n after [[, keeps ending \n before ]]
set( msg [[
multiline
string
]])
message( "<${msg}>\n" )

message("
--------------------------------------------------------------------------------
search, replace, regex")

set( pattern ${foo} )
set( repl ${zab} )
set( regex "FO+" )

message( "
input   ${input}
pattern ${pattern}
repl    ${repl}
regex   ${regex}
")

string( FIND ${input} ${pattern} index )
message( "find \${input} \${pattern} index                 = ${index}" )

string( FIND ${input} ${pattern} index REVERSE )
message( "find \${input} \${pattern} index reverse         = ${index}" )

string( REPLACE ${pattern} ${repl} output ${input} )
message( "replace \${pattern} \${repl} output \${input}     = ${output}  # replace all" )

string( REGEX MATCH ${regex} output ${input} )
message( "regex match \${regex} output \${input}           = ${output}" )

string( REGEX MATCHALL ${regex} output ${input} )
message( "regex matchall \${regex} output \${input}        = ${output}" )

string( REGEX REPLACE ${regex} ${repl} output ${input} )
message( "regex replace \${regex} \${repl} output \${input} = ${output}" )


message("
--------------------------------------------------------------------------------
regular expressions")

set( input "foo0123+baz" )
message( "input = <${input}>\n" )

string( REGEX MATCH "^foo" output ${input} )
message( "^foo      = <${output}>" )

string( REGEX MATCH "baz$" output ${input} )
message( "baz$      = <${output}>" )

string( REGEX MATCH "." output ${input} )
message( ".         = <${output}>" )

string( REGEX MATCH "foo.bar" output "foo\nbar fooXbar" )
string( REPLACE "\n" "\\n" output ${output} )  # encode \n for nicer output
message( "foo.bar   = <${output}>  # . matches \\n" )

string( REGEX MATCH "[1-9]" output ${input} )
message( "[1-9]     = <${output}>" )

#----------
message("")
# All the lovely Perl special chars have no meaning in CMake:
# \b = (^|[^a-zA-Z0-9_])word  word boundary, before word
#   or word($|[^a-zA-Z0-9_])  word boundary, after word
# \B                    not word boundary
# \d = [0-9]            digits
# \D = [^0-9]           non-digits
# \h = [ \t]            horiz space (todo confirm)
# \H = [^ \t]           not horiz space
# \v = [\n\r\L]         vertical space (todo confirm)
# \V = [^\n\r\L]        not vertical space
# \w = [a-zA-Z0-9_]     word chars
# \W = [^a-zA-Z0-9_]    not word chars
# \s = [ \t\n\r\L]      space (\L = page break; todo confirm)
# \S = [^ \t\n\r\L]     not space
string( REGEX MATCH [[\b\B\d\D\h\H\w\W\s\S]] output "___bBdDhHwWsS___" )
message( [[\b\B\d\D\h\H\w\W\s\S]] " = <${output}>" )

#----------
message("")
set( regex "(^|[^a-zA-Z0-9_])LP64" )
message( "\\bLP64 ~~ ${regex}" )
foreach (input "LP64" "stuff LP64" "stuff (LP64)"
             "ILP64" "stuff ILP64" "stuff (ILP64)")
    string( REGEX MATCH ${regex} output ${input} )
    message( "match input <${input}> = <${output}>" )
endforeach()

#----------
message("")

string( REGEX MATCH "3+b" output ${input} )
message( "3+b       = <${output}>" )

# Invalid escape sequence \+
#set( regex "3\+b" )

set( regex "3\\+b" )
string( REGEX MATCH ${regex} output ${input} )
message( "\"3\\\\+b\"   = <${output}>  # regex is ${regex}; extra \\ due to quoting" )

set( regex [[3\+b]] )
string( REGEX MATCH ${regex} output ${input} )
message( "[[3\\+b]]  = <${output}>  # regex is ${regex}; raw string [[...]] to avoid extra \\" )

#----------
message("")

string( REGEX MATCH "(foo|baz)(01)2" output ${input} )
message( "(foo|baz)(01)2 = <${output}>  # output is whole match" )
message( "CMAKE_MATCH_0  = <${CMAKE_MATCH_0}>  # whole match" )
message( "CMAKE_MATCH_1  = <${CMAKE_MATCH_1}>     # 1st ()" )
message( "CMAKE_MATCH_2  = <${CMAKE_MATCH_2}>      # 2nd ()" )
message( "CMAKE_MATCH_3  = <${CMAKE_MATCH_3}>        # 3rd (), non-existent" )
message( "... up to  _9" )

#----------
message("")
message( "regex  input  = output" )

string( REGEX MATCH "a_*b" output "ab" )
message( "a_*b   ab     = <${output}>" )

string( REGEX MATCH "a_*b" output "a_b" )
message( "a_*b   a_b    = <${output}>" )

string( REGEX MATCH "a_*b" output "a___b" )
message( "a_*b   a___b  = <${output}>" )

#----------
message("")

string( REGEX MATCH "a_+b" output "ab" )
message( "a_+b   ab     = <${output}>  # no match" )

string( REGEX MATCH "a_+b" output "a_b" )
message( "a_+b   a_b    = <${output}>" )

string( REGEX MATCH "a_+b" output "a___b" )
message( "a_+b   a___b  = <${output}>" )

#----------
message("")

string( REGEX MATCH "a_?b" output "ab" )
message( "a_?b   ab     = <${output}>" )

string( REGEX MATCH "a_?b" output "a_b" )
message( "a_?b   a_b    = <${output}>" )

string( REGEX MATCH "a_?b" output "a___b" )
message( "a_?b   a___b  = <${output}>  # no match" )

message("
--------------------------------------------------------------------------------
manipulation
inout = ${foo} for each line
")

set( inout ${foo} )
string( APPEND inout ${bar} )
message( "append  inout \${bar}          = ${inout}" )

set( inout ${foo} )
string( APPEND inout ${empty} )
message( "append  inout \${empty}        = ${inout}" )

set( inout ${foo} )
string( PREPEND inout ${bar} )
message( "prepend inout \${bar}          = ${inout}" )

set( inout ${foo} )
string( PREPEND inout ${empty} )
message( "prepend inout \${empty}        = ${inout}" )

string( CONCAT output ${bar} ${zab} )
message( "concat  output \${bar} \${zab}  = ${output}" )

string( JOIN ":" output ${foo} ${bar} ${zab} )
message( "join \":\" output \${foo} \${bar} \${zab} = ${output}" )

message("")

string( TOLOWER ${input} output )
message( "tolower \${input} output       = ${output}" )

string( TOLOWER "${empty}" output )
message( "tolower \"\${empty}\" output     = ${output}" )

string( TOUPPER ${input} output )
message( "toupper \${input} output       = ${output}" )

string( TOUPPER "${empty}" output )
message( "toupper \"\${empty}\" output     = ${output}" )

string( LENGTH ${input} output )
message( "length \${input} output        = ${output}" )

string( LENGTH "${empty}" output )
message( "length \"\${empty}\" output      = ${output}" )

string( SUBSTRING ${input} 2 4 output )
message( "substring \${input} 2 4 output             = ${output}" )

set( begin 2 )
set( len 4 )
string( SUBSTRING ${input} ${begin} ${len} output )
message( "substring \${input} \${begin} \${len} output = ${output}" )

# start must be inside string; len can extend beyond end (CMake > 3)
string( SUBSTRING "${empty}" 0 4 output )
message( "substring \"\${empty} 0 4 output            = ${output}  # begin must = 0" )

set( input "  ${input}  " )
message( "\ninput                       = <${input}>" )

string( STRIP ${input} output )
message( "strip \${input} output       = <${output}>" )

string( STRIP "${empty}" output )
message( "strip \"\${empty}\" output     = <${output}>" )

# strip generator eapressions $<...>
set( input "  ${foo}\$<BOOL:foo>${bar}  " )
message( "\ninput                       = <${input}>" )

string( GENEX_STRIP ${input} output )
message( "genex_strip \${input} output = <${output}>" )

set( input "${foo}_" )
set( count 4 )
message( "\ninput = ${input}" )
message( "count = ${count}" )
string( REPEAT ${input} ${count} output )
message( "repeat \${input} \${count} output = <${output}>" )

message("
--------------------------------------------------------------------------------
compare
")

string( COMPARE LESS ${foo} ${bar} output )
message( "compare <  \${foo} \${bar} output = <${output}>" )

string( COMPARE LESS_EQUAL ${foo} ${bar} output )
message( "compare <= \${foo} \${bar} output = <${output}>" )

string( COMPARE GREATER ${foo} ${bar} output )
message( "compare >  \${foo} \${bar} output = <${output}>" )

string( COMPARE GREATER_EQUAL ${foo} ${bar} output )
message( "compare >= \${foo} \${bar} output = <${output}>" )

string( COMPARE EQUAL ${foo} ${bar} output )
message( "compare == \${foo} \${bar} output = <${output}>" )

string( COMPARE NOTEQUAL ${foo} ${bar} output )
message( "compare != \${foo} \${bar} output = <${output}>" )

message("
--------------------------------------------------------------------------------
utilities
")

string( MD5 output ${input} )
message( "md5 output \${input} = <${output}>" )

string( SHA1 output ${input} )
message( "sha1 output \${input} = <${output}>" )
message( "other hashes:
    SHA224
    SHA256
    SHA384
    SHA512
    SHA3_224
    SHA3_256
    SHA3_384
    SHA3_512")

# chr: 32 = space, 102 = f, 111 = o
string( ASCII 32 102 111 111 output )
message( "ascii 32 102 111 111 output = <${output}>" )

set( input "#cmakedefine HAVE_BLAS\n#cmakedefine foo" )
message( "\ninput =\n${input}" )

string( CONFIGURE ${input} output )
message( "\nconfigure \${input} =\n${output}\n" )

set( input "c++ foo%bar^baz" )
message( "input = ${input}" )

string( MAKE_C_IDENTIFIER ${input} output )
message( "make_c_identifier \${input} = ${output}" )

string( RANDOM output )
message( "random output = ${output}  # default length 5" )

set( len 10 )
string( RANDOM LENGTH ${len} output )
message( "random length \${len} = ${output}" )

set( letters 0123456789abcdef )
string( RANDOM LENGTH ${len} ALPHABET ${letters} output )
message( "random length \${len} alphabet \${letters} = ${output}" )

string( TIMESTAMP output )
message( "timestamp output  = ${output}  # default" )

set( format "%Y-%b-%d %H:%M:%S" )
message( "format = ${format}" )
string( TIMESTAMP output ${format} )
message( "timestamp output \${format} = ${output}" )

set( ns "aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa" )
set( name "bar" )
string( UUID output NAMESPACE ${ns} NAME ${name} TYPE MD5 )
message( "UUID output NAMESPACE \${ns} NAME \${name} TYPE MD5 = ${output}" )

message("
--------------------------------------------------------------------------------
random tests
")

set( mylist "DEFINED foo;DEFINED CACHE{foo};CACHE{foo};ENV{foo}" )
foreach (item IN LISTS mylist )
    message( "<${item}>" )
    if (item MATCHES "DEFINED \\w+")
        message( "<${item}> matches" )
    else()
        message( "<${item}> does not match" )
    endif()
endforeach()

message("")
