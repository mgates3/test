# Tests what CMake accepts as true or false.
# See https://cmake.org/cmake/help/latest/command/if.html?highlight=TRUE

cmake_minimum_required( VERSION 3.0 )

project( Test )

message("
-------------------------------------------------------------------------------
All are true")

set( one 1 )
set( two 2 )
set( foo foo )  # random string

if (one)
    message("one   ${one}    is true")
else()
    message("one   ${one}    is false ***")
endif()

# if statements can use variable with or without ${} syntax.
if (${one})
    message("one   ${one}    is true")
else()
    message("one   ${one}    is false ***")
endif()

if (two)
    message("two   ${two}    is true")
else()
    message("two   ${two}    is false ***")
endif()

if (${two})
    message("two   ${two}    is true")
else()
    message("two   ${two}    is false ***")
endif()

if (foo)
    message("foo   ${foo}  is true")
else()
    message("foo   ${foo}  is false ***")
endif()

if (${foo})
    message("foo   ${foo}  is true")
else()
    message("foo   ${foo}  is false ***")
endif()

#--------------------
set( true1 TRUE )
set( true2 true )
set( true3 True )

if (true1)
    message("true1 ${true1} is true")
else()
    message("true1 ${true1} is false ***")
endif()

if (true2)
    message("true2 ${true2} is true")
else()
    message("true2 ${true2} is false ***")
endif()

if (true3)
    message("true3 ${true3} is true")
else()
    message("true3 ${true3} is false ***")
endif()

#--------------------
set( on1 ON )
set( on2 on )
set( on3 On )

if (on1)
    message("on1   ${on1}   is true")
else()
    message("on1   ${on1}   is false ***")
endif()

if (on2)
    message("on2   ${on2}   is true")
else()
    message("on2   ${on2}   is false ***")
endif()

if (on3)
    message("on3   ${on3}   is true")
else()
    message("on3   ${on3}   is false ***")
endif()

#--------------------
set( yes1 YES )
set( yes2 yes )
set( yes3 Yes )
set( yes4 Y )
set( yes5 y )

if (yes1)
    message("yes1  ${yes1}  is true")
else()
    message("yes1  ${yes1}  is false ***")
endif()

if (yes2)
    message("yes2  ${yes2}  is true")
else()
    message("yes2  ${yes2}  is false ***")
endif()

if (yes3)
    message("yes3  ${yes3}  is true")
else()
    message("yes3  ${yes3}  is false ***")
endif()

if (yes4)
    message("yes4  ${yes4}    is true")
else()
    message("yes4  ${yes4}    is false ***")
endif()

if (yes5)
    message("yes5  ${yes5}    is true")
else()
    message("yes5  ${yes5}    is false ***")
endif()

message("
-------------------------------------------------------------------------------
All are false, except notfound and NotFound.")

set( zero 0 )
set( empty "" )
# undef is undefined

if (zero)
    message("zero   ${zero}     is true ***")
else()
    message("zero   ${zero}     is false")
endif()

if (empty)
    message("empty  ${empty}      is true ***")
else()
    message("empty  ${empty}      is false")
endif()

if (${empty})
    message("empty  ${empty}      is true ***")
else()
    message("empty  ${empty}      is false")
endif()

if (undef)
    message("undef  ${undef}      is true ***")
else()
    message("undef  ${undef}      is false")
endif()

if (${undef})
    message("undef  ${undef}      is true ***")
else()
    message("undef  ${undef}      is false")
endif()

#--------------------
set( false1 FALSE )
set( false2 false )
set( false3 False )

if (false1)
    message("false1 ${false1} is true ***")
else()
    message("false1 ${false1} is false")
endif()

if (false2)
    message("false2 ${false2} is true ***")
else()
    message("false2 ${false2} is false")
endif()

if (false3)
    message("false3 ${false3} is true ***")
else()
    message("false3 ${false3} is false")
endif()

#--------------------
set( off1 OFF )
set( off2 off )
set( off3 Off )

if (off1)
    message("off1   ${off1}   is true ***")
else()
    message("off1   ${off1}   is false")
endif()

if (off2)
    message("off2   ${off2}   is true ***")
else()
    message("off2   ${off2}   is false")
endif()

if (off3)
    message("off3   ${off3}   is true ***")
else()
    message("off3   ${off3}   is false")
endif()

#--------------------
set( no1 NO )
set( no2 no )
set( no3 No )
set( no4 N )
set( no5 n )

if (no1)
    message("no1    ${no1}    is true ***")
else()
    message("no1    ${no1}    is false")
endif()

if (no2)
    message("no2    ${no2}    is true ***")
else()
    message("no2    ${no2}    is false")
endif()

if (no3)
    message("no3    ${no3}    is true ***")
else()
    message("no3    ${no3}    is false")
endif()

#--------------------
set( ignore1 IGNORE )
set( ignore2 ignore )
set( ignore3 Ignore )

if (ignore1)
    message("ignore1   ${ignore1}   is true ***")
else()
    message("ignore1   ${ignore1}   is false")
endif()

if (ignore2)
    message("ignore2   ${ignore2}   is true ***")
else()
    message("ignore2   ${ignore2}   is false")
endif()

if (ignore3)
    message("ignore3   ${ignore3}   is true ***")
else()
    message("ignore3   ${ignore3}   is false")
endif()

#--------------------
set( notfound1 NOTFOUND )
set( notfound2 notfound )  # considered true
set( notfound3 NotFound )  # considered true

if (notfound1)
    message("notfound1 ${notfound1} is true ***")
else()
    message("notfound1 ${notfound1} is false")
endif()

if (notfound2)
    message("notfound2 ${notfound2} is true ***")
else()
    message("notfound2 ${notfound2} is false")
endif()

if (notfound3)
    message("notfound3 ${notfound3} is true ***")
else()
    message("notfound3 ${notfound3} is false")
endif()

message("")
