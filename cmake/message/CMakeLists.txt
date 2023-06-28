# Tests message log levels.
# cmake --log-level=<ERROR|WARNING|NOTICE|STATUS|VERBOSE|DEBUG|TRACE> ..

cmake_minimum_required( VERSION 3.0 )

project( Test )

message( "CMAKE_MESSAGE_LOG_LEVEL '${CMAKE_MESSAGE_LOG_LEVEL}'" )

message( "---------------------------------------- level 6: trace" )
# -- trace message
# -- multiline trace message
#     line 2
#     line 3
message( TRACE "trace message" )
message( TRACE
    "multiline trace message
    line 2
    line 3" )

message( "---------------------------------------- level 5: debug" )
# -- debug message
# -- multiline debug message
#     line 2
#     line 3
message( DEBUG "debug message" )
message( DEBUG
    "multiline debug message
    line 2
    line 3" )

message( "---------------------------------------- level 4: verbose" )
# -- verbose message
# -- multiline verbose message
#     line 2
#     line 3
message( VERBOSE "verbose message" )
message( VERBOSE
    "multiline verbose message
    line 2
    line 3" )

message( "---------------------------------------- level 3: status" )
# -- status message
# -- multiline status message
#     line 2
#     line 3
message( STATUS "status message" )
message( STATUS
    "multiline status message
    line 2
    line 3" )

message( "---------------------------------------- level 2: default" )
# default message
# multiline default message
#     line 2
#     line 3
message( "default message" )
message(
    "multiline default message
    line 2
    line 3" )

message( "---------------------------------------- level 2: notice" )
# [same as default]
# notice message
# multiline notice message
#     line 2
#     line 3
message( NOTICE "notice message" )
message( NOTICE
    "multiline notice message
    line 2
    line 3" )

message( "---------------------------------------- level 1: author_warning" )
# CMake Warning (dev) at CMakeLists.txt:58 (message):
#   author_warning message
# This warning is for project developers.  Use -Wno-dev to suppress it.
#
message( AUTHOR_WARNING "author_warning message" )
message( AUTHOR_WARNING
    "multiline author_warning message
    line 2
    line 3" )

message( "---------------------------------------- level 1: deprecation warning" )
# CMake Deprecation Warning at CMakeLists.txt:85 (message):
#   deprecation message
#
#
message( DEPRECATION "deprecation message" )
message( DEPRECATION
    "multiline deprecation message
    line 2
    line 3" )

message( "---------------------------------------- level 1: warning" )
# CMake Warning at CMakeLists.txt:51 (message):
#   warning message
#
#
message( WARNING "warning message" )
message( WARNING
    "multiline warning message
    line 2
    line 3" )

message( "---------------------------------------- level 0: send error" )
# CMake Error at CMakeLists.txt:92 (message):
#   send_error message
#
#
# [and later at end:]
# -- Configuring incomplete, errors occurred!
# See also "/Users/mgates/Documents/test/cmake/message/build/CMakeFiles/CMakeOutput.log".
message( SEND_ERROR "send_error message" )
message( SEND_ERROR
    "multiline send_error message
    line 2
    line 3" )

message( "---------------------------------------- level 0: fatal error" )
# CMake Error at CMakeLists.txt:99 (message):
#   fatal_error message
#
#
# [stops execution, and later at end:]
# -- Configuring incomplete, errors occurred!
## message( FATAL_ERROR "fatal_error message" )
## message( FATAL_ERROR
##     "multiline fatal_error message
##     line 2
##     line 3" )

message("")
