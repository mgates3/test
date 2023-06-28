# Tests CMake if conditions.
# See https://cmake.org/cmake/help/latest/command/if.html

cmake_minimum_required( VERSION 3.8 )
# 3.3 required for IN_LIST
# 3.4 required for TEST
# 3.14 required for ENV, CACHE

project( Test )

message( "
--------------------------------------------------------------------------------
symbols
" )

add_executable(tester tester.cc)
set( mycache 123 CACHE INTERNAL "doc" )

set( mylist "foo;foreach;tester;mylist;mycache;PATH" )
foreach (item IN ITEMS ${mylist})
    if (COMMAND ${item})
        message("${item} is command ***")
    else()
        message("${item} not command")
    endif()

    if (POLICY ${item})
        message("${item} is policy ***")
    else()
        message("${item} not policy")
    endif()

    if (TARGET ${item})
        message("${item} is target ***")
    else()
        message("${item} not target")
    endif()

    # CMake 3.4
    if (TEST ${item})
        message("${item} is test ***")
    else()
        message("${item} not test")
    endif()

    if (DEFINED ${item})
        message("${item} is defined ***")
    else()
        message("${item} not defined")
    endif()

    # CMake 3.14
    if (DEFINED CACHE{${item}})
        message("${item} is cache ***  # CMake 3.14")
    else()
        message("${item} not cache")
    endif()

    # Syntax error
    #if (CACHE ${item})
    #    message("${item} is cache ***")
    #else()
    #    message("${item} not cache")
    #endif()

    # CMake 3.14
    if (DEFINED ENV{${item}})
        message("${item} is env ***  # CMake 3.14")
    else()
        message("${item} not env")
    endif()

    # Syntax error
    #if (ENV ${item})
    #    message("${item} is env ***")
    #else()
    #    message("${item} not env")
    #endif()

    message("")
endforeach()

message( "
--------------------------------------------------------------------------------
files
" )

# Files are relative to the build directory.
set(items "../foo;../CMakeLists.txt;../build;../sym;/usr/bin/less;/foo/bar/baz")
foreach (item IN LISTS items)
    if (EXISTS ${item})
        message("${item} exists ***")
    else()
        message("${item} not exists")
    endif()

    # True if either or both files don't exist.
    if (${item} IS_NEWER_THAN "../tester.cc")
        message("${item} newer ***")
    else()
        message("${item} not newer")
    endif()

    if ("../tester.cc" IS_NEWER_THAN ${item})
        message("${item} older ***")
    else()
        message("${item} not older")
    endif()

    if (IS_DIRECTORY ${item})
        message("${item} dir ***")
    else()
        message("${item} not dir")
    endif()

    if (IS_SYMLINK ${item})
        message("${item} symlink ***")
    else()
        message("${item} not symlink")
    endif()

    if (IS_ABSOLUTE ${item})
        message("${item} absolute ***")
    else()
        message("${item} not absolute")
    endif()

    message("")
endforeach()

#--------------------
#
message( "
--------------------------------------------------------------------------------
Numeric EQUAL, GREATER, ..., using unquoted (a OPERATOR b) syntax
These work if a or b is empty, in which case it is always false." )

set( a_list ";1;0;-1" )

foreach (a IN LISTS a_list)
foreach (b IN LISTS a_list)
    message( "\nnested a = <${a}>, b = <${b}>" )

    if (a EQUAL b)
        message("${a} == ${b}")
    endif()

    if (a GREATER b)
        message("${a} >  ${b}")
    endif()

    if (a GREATER_EQUAL b)
        message("${a} >= ${b}")
    endif()

    if (a LESS b)
        message("${a} <  ${b}")
    endif()

    if (a LESS_EQUAL b)
        message("${a} <= ${b}")
    endif()

    if (NOT a LESS_EQUAL b)
        message("NOT ${a} <= ${b} is NOT (${a} <= ${b})")
    endif()

    # NOT has low precedence, unlike in C
    if ((NOT a) LESS_EQUAL b)
        message("(NOT ${a}) <= ${b}")
    endif()
endforeach()
endforeach()

message( "
--------------------------------------------------------------------------------
Numeric EQUAL, GREATER, ..., using \${} (\${a} OPERATOR \${b}) syntax.
If a xor b is empty, these cause errors, but okay if both a and b are empty." )

set( a_list "1;0;-1" )
#set( a_list ";" )  # okay

foreach (a IN LISTS a_list)
foreach (b IN LISTS a_list)
    message( "\nnested a = <${a}>, b = <${b}>" )

    if (${a} EQUAL ${b})
        message("${a} == ${b}")
    endif()

    if (${a} GREATER ${b})
        message("${a} >  ${b}")
    endif()

    if (${a} GREATER_EQUAL ${b})
        message("${a} >= ${b}")
    endif()

    if (${a} LESS ${b})
        message("${a} <  ${b}")
    endif()

    if (${a} LESS_EQUAL ${b})
        message("${a} <= ${b}")
    endif()
endforeach()
endforeach()

message( "
--------------------------------------------------------------------------------
String STREQUAL, STRGREATER, ..., using unquoted (a op b) syntax" )

set( a_list ";abc;foo;bar" )

set( a "" )
message( "define a = <${a}>" )
if (a STREQUAL x)
    message("<${a}> == <${x}>")
else()
    message("NOT <${a}> == <${x}>")
endif()
if ("${a}" STREQUAL "${x}")
    message("<${a}> == <${x}>")
else()
    message("NOT <${a}> == <${x}>")
endif()

set( x "" )
message( "define x = <${x}>" )
if (a STREQUAL x)
    message("<${a}> == <${x}>")
else()
    message("NOT <${a}> == <${x}>")
endif()
if ("${a}" STREQUAL "${x}")
    message("<${a}> == <${x}>")
else()
    message("NOT <${a}> == <${x}>")
endif()

foreach (a IN LISTS a_list)
foreach (b IN LISTS a_list)
    message( "\nnested a = <${a}>, b = <${b}>" )

    if (a STREQUAL b)
        message("<${a}> == <${b}>")
    endif()

    if (a STRGREATER b)
        message("<${a}> >  <${b}>")
    endif()

    if (a STRGREATER_EQUAL b)
        message("<${a}> >= <${b}>")
    endif()

    if (a STRLESS b)
        message("<${a}> <  <${b}>")
    endif()

    if (a STRLESS_EQUAL b)
        message("<${a}> <= <${b}>")
    endif()
endforeach()
endforeach()

message( "
--------------------------------------------------------------------------------
String STREQUAL, STRGREATER, ..., using quoted (\${a} op \${b}) syntax" )

set( a_list "abc;foo;foobar" )

foreach (a IN LISTS a_list)
foreach (b IN LISTS a_list)
    message( "\nnested a = <${a}>, b = <${b}>" )

    if (${a} STREQUAL ${b})
        message("<${a}> == <${b}>")
    endif()

    if (${a} STRGREATER ${b})
        message("<${a}> >  <${b}>")
    endif()

    if (${a} STRGREATER_EQUAL ${b})
        message("<${a}> >= <${b}>")
    endif()

    if (${a} STRLESS ${b})
        message("<${a}> <  <${b}>")
    endif()

    if (${a} STRLESS_EQUAL ${b})
        message("<${a}> <= <${b}>")
    endif()
endforeach()
endforeach()

message( "
--------------------------------------------------------------------------------
version
" )

set( a_list "1.0;2.0;2.0.1;2.13.1;2.4.3" )
foreach (a IN LISTS a_list)
    message( "-----" )
    foreach (b IN LISTS a_list)
        if (${a} VERSION_EQUAL ${b})
            message( "${a} == ${b}" )
        else()
            message( "${a} != ${b}" )
        endif()

        if (${a} VERSION_GREATER ${b})
            message( "${a} >  ${b}" )
        #else()
        #    message( "${a} == ${b}" )
        endif()

        if (${a} VERSION_GREATER_EQUAL ${b})
            message( "${a} >= ${b}" )
        #else()
        #    message( "${a} == ${b}" )
        endif()

        if (${a} VERSION_LESS ${b})
            message( "${a} <  ${b}" )
        #else()
        #    message( "${a} == ${b}" )
        endif()

        if (${a} VERSION_LESS_EQUAL ${b})
            message( "${a} <= ${b}" )
        #else()
        #    message( "${a} == ${b}" )
        endif()

        message("")
    endforeach()
endforeach()

message( "
--------------------------------------------------------------------------------
in list (CMake 3.3)
" )

set( a_list "foobar;bar;baz" )
set( b_list "foobar;zab;foo" )
message( "a_list ${a_list}\n" )

foreach (b IN LISTS b_list)
    # plain syntax
    if (b IN_LIST a_list)
        message("b    = ${b} found")
    else()
        message("b    = ${b} not found")
    endif()

    # $ syntax.
    if (${b} IN_LIST a_list)
        message("\${b} = ${b} found")
    else()
        message("\${b} = ${b} not found")
    endif()

    # Syntax error
    # if (${b} IN_LIST ${a_list})
    #     message("${b} found")
    # endif()
    # if (b IN_LIST ${a_list})
    #     message("${b} found")
    # endif()
endforeach()

message( "
--------------------------------------------------------------------------------
pathological cases
" )

set( a "b" )
set( b "1" )

if (a STREQUAL "b")
    message("a == b")
else()
    message("a != b")
endif()

if (${a} STREQUAL "b")
    message("\${a} == b")
else()
    message("\${a} != b")
endif()

if ("${a}" STREQUAL "b")
    message("\"\${a}\" == b")
else()
    message("\"\${a}\" != b")
endif()

#-----
if (c STREQUAL "b")
    message("c == b")
else()
    message("c != b")
endif()

# syntax error
# if (${c} STREQUAL "b")
#     message("\${c} == b")
# else()
#     message("\${c} != b")
# endif()

if ("${c}" STREQUAL "b")
    message("\"\${c}\" == b")
else()
    message("\"\${c}\" != b")
endif()

message( "
--------------------------------------------------------------------------------
STREQUAL, comparing syntaxes
" )

set( a_list ";a;b" )
set( b_list ";a;b" )

unset( a CACHE )
unset( b CACHE )

message( "---------- a, b both unset" )
unset( a )
unset( b )
    message( "a='${a}', b='${b}'" )
    if ("${a}" STREQUAL "${b}")
        if (a STREQUAL b)
            message( "       a   STREQUAL    b" )
        else()
            message( "NOT    a   STREQUAL    b    <= !!" )
        endif()
        message( "    \"\${a}\" STREQUAL \"\${b}\"" )
    else()
        if (a STREQUAL b)
            message( "       a   STREQUAL    b    <= !!" )
        else()
            message( "NOT    a   STREQUAL    b" )
        endif()
        message( "NOT \"\${a}\" STREQUAL \"\${b}\"" )
    endif()
    message( "" )

message( "---------- a set, b unset" )
unset( b )

foreach (a IN LISTS a_list)
    message( "a='${a}', b='${b}'" )
    if ("${a}" STREQUAL "${b}")
        if (a STREQUAL b)
            message( "       a   STREQUAL    b" )
        else()
            message( "NOT    a   STREQUAL    b    <= !!" )
        endif()
        message( "    \"\${a}\" STREQUAL \"\${b}\"" )
    else()
        if (a STREQUAL b)
            message( "       a   STREQUAL    b    <= !!" )
        else()
            message( "NOT    a   STREQUAL    b" )
        endif()
        message( "NOT \"\${a}\" STREQUAL \"\${b}\"" )
    endif()
    message( "" )
endforeach()

message( "---------- a unset, b set" )
unset( a )

foreach (b IN LISTS b_list)
    message( "a='${a}', b='${b}'" )
    if ("${a}" STREQUAL "${b}")
        if (a STREQUAL b)
            message( "       a   STREQUAL    b" )
        else()
            message( "NOT    a   STREQUAL    b    <= !!" )
        endif()
        message( "    \"\${a}\" STREQUAL \"\${b}\"" )
    else()
        if (a STREQUAL b)
            message( "       a   STREQUAL    b    <= !!" )
        else()
            message( "NOT    a   STREQUAL    b" )
        endif()
        message( "NOT \"\${a}\" STREQUAL \"\${b}\"" )
    endif()
    message( "" )
endforeach()

message( "---------- a, b both set" )
foreach (a IN LISTS a_list)
foreach (b IN LISTS b_list)
    message( "a='${a}', b='${b}'" )
    if ("${a}" STREQUAL "${b}")
        if (a STREQUAL b)
            message( "       a   STREQUAL    b" )
        else()
            message( "NOT    a   STREQUAL    b    <= !!" )
        endif()
        message( "    \"\${a}\" STREQUAL \"\${b}\"" )
    else()
        if (a STREQUAL b)
            message( "       a   STREQUAL    b    <= !!" )
        else()
            message( "NOT    a   STREQUAL    b" )
        endif()
        message( "NOT \"\${a}\" STREQUAL \"\${b}\"" )
    endif()
    message( "" )
endforeach()
endforeach()

message( "
--------------------------------------------------------------------------------
" )

unset( a )

if (a)
    message( "a '${a}' (unset)" )
else()
    message( "not a '${a}' (unset)" )
endif()

set( a "" )

if (a)
    message( "a '${a}' (empty)" )
else()
    message( "not a '${a}' (empty)" )
endif()

set( a " " )

if (a)
    message( "a '${a}'" )
else()
    message( "not a '${a}'" )
endif()

set( a "foo" )

if (a)
    message( "a '${a}'" )
else()
    message( "not a '${a}'" )
endif()

set( a true )

if (a)
    message( "a '${a}'" )
else()
    message( "not a '${a}'" )
endif()

set( a false )

if (a)
    message( "a '${a}'" )
else()
    message( "not a '${a}'" )
endif()

set( a on )

if (a)
    message( "a '${a}'" )
else()
    message( "not a '${a}'" )
endif()

set( a off )

if (a)
    message( "a '${a}'" )
else()
    message( "not a '${a}'" )
endif()

message( "
--------------------------------------------------------------------------------
OR conditionals
" )

unset( a )
unset( b )
if (a OR b)
    message( "    a '${a}'  OR b '${b}'  (both unset)" )
else()
    message( "not a '${a}'  OR b '${b}'  (both unset)" )
endif()

set( a "" )
unset( b )
if (a OR b)
    message( "    a '${a}'  OR b '${b}'  (b unset)" )
else()
    message( "not a '${a}'  OR b '${b}'  (b unset)" )
endif()

set( a "x" )
unset( b )
if (a OR b)
    message( "    a '${a}' OR b '${b}'  (b unset)" )
else()
    message( "not a '${a}' OR b '${b}'  (b unset)" )
endif()

unset( a )
set( b "" )
if (a OR b)
    message( "    a '${a}'  OR b '${b}'  (a unset)" )
else()
    message( "not a '${a}'  OR b '${b}'  (a unset)" )
endif()

unset( a )
set( b "x" )
if (a OR b)
    message( "    a '${a}'  OR b '${b}' (a unset)" )
else()
    message( "not a '${a}'  OR b '${b}' (a unset)" )
endif()

set( a "" )
set( b "" )
if (a OR b)
    message( "    a '${a}'  OR b '${b}'" )
else()
    message( "not a '${a}'  OR b '${b}'" )
endif()

set( a "x" )
set( b "" )
if (a OR b)
    message( "    a '${a}' OR b '${b}'" )
else()
    message( "not a '${a}' OR b '${b}'" )
endif()

set( a "" )
set( b "x" )
if (a OR b)
    message( "    a '${a}'  OR b '${b}'" )
else()
    message( "not a '${a}'  OR b '${b}'" )
endif()

set( a "x" )
set( b "y" )
if (a OR b)
    message( "    a '${a}' OR b '${b}'" )
else()
    message( "not a '${a}' OR b '${b}'" )
endif()

message( "
--------------------------------------------------------------------------------
" )

if (xyz)
    message( "xyz true" )
else()
    message( "xyz false" )
endif()
if (DEFINED xyz)
    message( "xyz defined" )
else()
    message( "xyz not defined" )
endif()

set( xyz "0" )
if (xyz)
    message( "xyz true" )
else()
    message( "xyz false" )
endif()
if (DEFINED xyz)
    message( "xyz defined" )
else()
    message( "xyz not defined" )
endif()

set( xyz "1" )
if (xyz)
    message( "xyz true" )
else()
    message( "xyz false" )
endif()
if (DEFINED xyz)
    message( "xyz defined" )
else()
    message( "xyz not defined" )
endif()

message( "
--------------------------------------------------------------------------------
" )
