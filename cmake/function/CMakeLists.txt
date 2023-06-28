# Tests function syntax, with optional arguments.
# Demonstrates use in debug function.

cmake_minimum_required( VERSION 3.15 )

project( Test CXX )

message("
--------------------------------------------------------------------------------
# Variables are case sensitive; some recommend UPPER.
# I might disagree: maybe internal variables should be lower?
")

set( FOO 1 )
set( foo 2 )
set( Foo 3 )

message( "FOO ${FOO}" )
message( "foo ${foo}" )
message( "Foo ${Foo}" )



message("
--------------------------------------------------------------------------------
# Functions are NOT case sensitive; recommend lowercase.
")

function( func msg )
    message( ${msg} )
endfunction()

func( "func" )
FUNC( "FUNC" )
Func( "Func" )



message("
--------------------------------------------------------------------------------
# Optional arguments
")

function( func_argv msg )
    message( "func_argv: ${msg}" )
    message( "ARGC  ${ARGC}"  )
    message( "ARGV0 ${ARGV0}" )
    message( "ARGV1 ${ARGV1}" )
    message( "ARGV2 ${ARGV2}" )
    message( "" )
endfunction()

func_argv( "one" )
func_argv( "two" 1 )
func_argv( "three" 1 2 )



message("
--------------------------------------------------------------------------------
# Local scope
")

function( func_scope msg )
    message( "func_scope: ${msg}" )
    message( "inside: scope1 = ${scope1}" )
    set( scope1 "inner1" )
    set( scope2 "inner2" )
    message( "inside: scope1 = ${scope1}" )
    message( "inside: scope2 = ${scope2}" )
    message( "" )
endfunction()

set( scope1 "global" )
func_scope( "one" )
message( "outside: scope1 = ${scope1}" )
message( "outside: scope2 = ${scope2}" )



message("
--------------------------------------------------------------------------------
# output variable
")

function( func_output input output_variable )
    message( "input   = ${input}" )
    message( "output  = ${output_variable}" )
    message( "output2 = ${${output_variable}}\n" )

    set( input "foo" )
    set( ${output_variable} "bar" PARENT_SCOPE )

    # after setting a variable that way, is there any way to read it again?
    # Nested dereferencing : ${${output_variable}} returns the original value,
    # not its new value.
    message( "input   = ${input}" )
    message( "output  = ${output_variable}" )
    message( "output2 = ${${output_variable}}\n" )
    #message( "output3 = ${${${output_variable}}}" )
endfunction()

set( a "aaa aaa" )
set( b "bbb bbb" )
message( "a ${a}" )
message( "b ${b}\n" )

func_output( ${a} b )
message( "a ${a}" )
message( "b ${b}" )


message("
--------------------------------------------------------------------------------
# debug() function
# Can be replaced with message( DEBUG msg ) and --log-level=DEBUG.
")

function( debug msg )
    set( level 1 )
    if (${ARGC} GREATER 1)
        set( level ${ARGV1} )
    endif()
    #message( "DEBUG ${DEBUG} level ${level}" )
    if ("${DEBUG}" GREATER_EQUAL ${level})
        message( "Debug: ${msg}" )
    endif()
endfunction()

message( "DEBUG = ${DEBUG}\n" )

debug( "default" )
debug( "level 1" 1 )
debug( "level 2" 2 )
DEBUG( "level 2" 2 )
Debug( "level 2" 2 )

message( "" )
