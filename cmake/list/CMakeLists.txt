# Tests CMake list functions.
# https://cmake.org/cmake/help/latest/command/list.html

cmake_minimum_required( VERSION 3.0 )

project( Test )

message("
--------------------------------------------------------------------------------
Read
")

set( mylist "a;b;c;b;d;abcd;defg" )
set( item "b" )
set( x "x" )
set( y "y" )
set( index 3 )  # zero based
message( "mylist              = ${mylist}" )
message( "item                = ${item}" )
message( "index               = ${index}" )

list( LENGTH mylist output )
message( "length mylist       = ${output}" )

list( GET mylist ${index} output )
message( "get mylist \${index} = ${output}  # zero based index" )

list( FIND mylist ${item} output )
message( "find mylist \${item} = ${output}  # zero based index" )

message("
--------------------------------------------------------------------------------
Modify
Each command starts with alist = ${mylist} and modifies it in-place.
")

message( "foo <${foo}>" )

list( APPEND foo "bar1" )
message( "foo <${foo}>" )

list( APPEND foo "bar2" )
message( "foo <${foo}>" )

list( APPEND foo "bar3" )
message( "foo <${foo}>" )

list( APPEND foo "bar4" )
message( "foo <${foo}>" )

list( APPEND foo "bar5;bar6;bar7" )
message( "foo <${foo}>" )

# Add items
set( alist ${mylist} )
list( APPEND alist "u" v )
message( "append alist \"u\" v              = ${alist}" )
message("")

message("Appending \"\" doesn't work on empty list.")
set( alist "" )
list( APPEND alist "" )
message( "append alist \"\"                 = ${alist}" )
list( APPEND alist "x" )
message( "append alist \"x\"                = ${alist}" )
list( APPEND alist "" )
message( "append alist \"\"                 = ${alist}" )
message("")

set( alist ";" )
message( "append alist \"\"                 = ${alist}" )
list( APPEND alist "" )
message( "append alist \"\"                 = ${alist}" )
message("")

set( alist ${mylist} )
list( APPEND alist ${x} ${y} )
message( "append alist \${x} \${y}          = ${alist}" )

set( alist ${mylist} )
list( PREPEND alist "u" v )
message( "prepend alist \"u\" v             = ${alist}" )

set( alist ${mylist} )
list( PREPEND alist ${x} ${y} )
message( "prepend alist ${x} ${y}               = ${alist}" )

set( alist ${mylist} )
list( INSERT alist ${index} "u" v )
message( "insert alist \${index} \"u\" v     = ${alist}" )

set( alist ${mylist} )
list( INSERT alist ${index} ${x} ${y} )
message( "insert alist \${index} \${x} \${y} = ${alist}" )

set( regex "c|d" )
message( "regex                           = ${regex}" )

# Filter items in-place
set( alist ${mylist} )
list( FILTER alist INCLUDE REGEX "c|d" )
message( "filter alist include (c|d)      = ${alist}" )

set( alist ${mylist} )
list( FILTER alist INCLUDE REGEX ${regex} )
message( "filter alist include \${regex}   = ${alist}" )

set( alist ${mylist} )
list( FILTER alist EXCLUDE REGEX "c|d" )
message( "filter alist exclude (c|d)      = ${alist}" )

set( alist ${mylist} )
list( FILTER alist EXCLUDE REGEX ${regex} )
message( "filter alist exclude \${regex}   = ${alist}" )

# Remove items
set( alist ${mylist} )
list( POP_BACK alist x )
message( "pop_back alist x                = ${alist}, x = ${x}" )

set( alist ${mylist} )
list( POP_BACK alist x y )
message( "pop_back alist x y              = ${alist},   x = ${x}, y = ${y}" )

set( alist ${mylist} )
list( POP_FRONT alist x )
message( "pop_front alist x               = ${alist}, x = ${x}" )

set( alist ${mylist} )
list( POP_FRONT alist x y )
message( "pop_front alist x y             = ${alist},   x = ${x}, y = ${y}" )

set( alist ${mylist} )
list( REMOVE_ITEM alist "b" )
message( "remove_item alist \"b\"           = ${alist}" )

set( alist ${mylist} )
list( REMOVE_AT alist ${index} )
message( "remove_at alist \${index}        = ${alist}" )

set( alist ${mylist} )
list( REMOVE_DUPLICATES alist )
message( "remove_duplicates alist         = ${alist}" )

set( alist ${mylist} )
list( REVERSE alist )
message( "reverse alist                   = ${alist}" )

set( alist ${mylist} )
list( SORT alist )
message( "sort alist                      = ${alist}" )

list( APPEND blist "b1" )
message( "blist ${blist}" )

list( APPEND blist "b2" )
message( "blist ${blist}" )

list( APPEND clist "c1" )
message( "clist ${clist}" )

list( APPEND clist "c2" )
message( "clist ${clist}" )

list( APPEND clist "${blist}" )
message( "clist ${clist}" )

message("")
