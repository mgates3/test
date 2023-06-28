# Tests what CMake accepts as true or false.
# See https://cmake.org/cmake/help/latest/command/if.html?highlight=TRUE

cmake_minimum_required( VERSION 3.0 )

project( Test )

message("
-------------------------------------------------------------------------------
foreach loops
loop variables are local in scope; see pre and post x")

set( a_list ";1;0;;-1" )
set( b_list "2;3" )

set( x "x original" )
message( "pre x = <${x}>" )
message( "a_list = <${a_list}>" )
message( "b_list = <${b_list}>" )

message( "\nforeach x a_list b_list" )
foreach (x a_list b_list)
    message( "x <${x}>" )
endforeach()

message( "\nforeach x \${a_list} \${b_list}" )
foreach (x ${a_list} ${b_list})
    message( "x <${x}>" )
endforeach()

message("
-------------------------------------------------------------------------------
foreach IN loops")

message( "\nforeach x IN LISTS strings" )
foreach (x IN LISTS ";1;0;;-1" "2;3")
    message( "    x <${x}>" )
endforeach()

message( "\nforeach x IN ITEMS strings" )
foreach (x IN ITEMS ";1;0;;-1" "2;3")
    message( "    x <${x}>" )
endforeach()

message( "\nforeach x IN LISTS a_list b_list" )
foreach (x IN LISTS a_list b_list)
    message( "    x <${x}>" )
endforeach()

message( "\nforeach x IN ITEMS a_list b_list" )
foreach (x IN ITEMS a_list b_list)
    message( "    x <${x}>" )
endforeach()

message( "\nforeach x IN LISTS \${a_list} \${b_list}" )
foreach (x IN LISTS ${a_list} ${b_list})
    message( "    x <${x}>" )
endforeach()

message( "\nforeach x IN ITEMS \${a_list} \${b_list}" )
message( "This misses empty items in the lists, so the documentation:" )
message( "    'The forms LISTS A and ITEMS ${A} are equivalent.' is subtly wrong." )
message( "Same as foreach x \${a_list} \${b_list}" )
foreach (x IN ITEMS ${a_list} ${b_list})
    message( "    x <${x}>" )
endforeach()

message("
-------------------------------------------------------------------------------
foreach RANGE loops")

message( "\nforeach x RANGE 4" )
foreach (x RANGE 4)
    message( "    x <${x}>" )
endforeach()

set( cnt 4 )
message( "\nforeach x RANGE cnt = ${cnt}" )
foreach (x RANGE cnt)
    message( "    x <${x}>" )
endforeach()

message( "\nforeach x RANGE \${cnt} = ${cnt}" )
foreach (x RANGE ${cnt})
    message( "    x <${x}>" )
endforeach()

message( "\nforeach x RANGE 2 5" )
foreach (x RANGE 2 5)
    message( "    x <${x}>" )
endforeach()

set( start 3 )
set( stop  6 )
message( "\nforeach x RANGE \${start} = ${start}, \${stop} = ${stop}" )
foreach (x RANGE ${start} ${stop})
    message( "    x <${x}>" )
endforeach()

message("
-------------------------------------------------------------------------------
foreach IN ZIP_LISTS loops (requires 3.17)")
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.17)

    #set( a_list "1;2;3;4" )
    #set( b_list "a;b;c;d" )

    list( APPEND c_list 1 2 3 4 )
    list( APPEND d_list a b c d )

    message( "c_list = <${c_list}>" )
    message( "d_list = <${d_list}>" )

    message( "\nforeach x y IN ZIP_LISTS c_list d_list" )
    foreach (xx yy IN ZIP_LISTS c_list d_list)
        message( "    xx <${xx}>, yy <${yy}>" )
    endforeach()
else()
    message( "skipping: using CMake ${CMAKE_VERSION}" )
endif()

message("
-------------------------------------------------------------------------------
while loops
conditional with same syntax as `if`, including i and \${i} syntax.")


message( "\nwhile (i > 0) { i -= 1 }" )
set( i 4 )
while (i GREATER 0)
    message( "    i ${i}" )
    math( EXPR i "${i} - 1" )
endwhile()

message( "\nwhile (\${i} > 0) { i -= 1 }" )
set( i 4 )
while (${i} GREATER 0)
    message( "    i ${i}" )
    math( EXPR i "${i} - 1" )
endwhile()

message( "\nwhile (\${i} > 0) { i -= 1 }" )
foreach (i IN LISTS a_list)
    message( "start i ${i}" )
    if (i EQUAL 1)
        message( "if i ${i}" )
    endif()
    while (i EQUAL 1)
        message( "    i ${i}" )
        math( EXPR i "${i} - 1" )
    endwhile()

    # For empty i, this `if` is an error, but the same `while` works fine. Ick!
    # if (${i} EQUAL 1)
    #     message( "if i ${i}" )
    # endif()
    while (${i} EQUAL 1)
        message( "    i ${i}" )
        math( EXPR i "${i} - 1" )
    endwhile()
endforeach()

message( "\nwhile (i > 0) { i -= 1 }" )
set( i 5 )
while (i GREATER 0)
    message( "    i ${i}" )

    math( EXPR i "${i} - 1" )
    message( "    i ${i} next" )

    if (i EQUAL 2)
        message( "        break" )
        break()
    endif()
    message( "        after break" )

    if (i EQUAL 4)
        message( "        continue" )
        continue()
    endif()
    message( "        after continue" )
endwhile()


message( "\npost x = <${x}>" )

message("")
