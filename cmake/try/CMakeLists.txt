# Tests CMake string functions
# https://cmake.org/cmake/help/latest/command/string.html

cmake_minimum_required( VERSION 3.0 )

project( Test )

# Why is this not set to true by default?
# When would you request a certain standard and it NOT be required?
message( "CMAKE_C_STANDARD_REQUIRED   = <${CMAKE_C_STANDARD_REQUIRED}>" )
message( "CMAKE_CXX_STANDARD_REQUIRED = <${CMAKE_CXX_STANDARD_REQUIRED}>" )

# Thankfully off by default.
message( "CMAKE_C_EXTENSIONS   = <${CMAKE_C_EXTENSIONS}>" )
message( "CMAKE_CXX_EXTENSIONS = <${CMAKE_CXX_EXTENSIONS}>" )

# BIN = project/build
# SRC = project
message( "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}" )
message( "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}" )

# Set to choose build config. I have no idea what that means.
message( "CMAKE_TRY_COMPILE_CONFIGURATION = ${CMAKE_TRY_COMPILE_CONFIGURATION}" )

message("
--------------------------------------------------------------------------------
try_compile
")

    try_compile(
        compile_result
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/simple.cc
    )

message( "compile result <${compile_result}>" )

message("
--------------------------------------------------------------------------------
try_compile
")

try_compile(
    compile_result
    ${CMAKE_CURRENT_BINARY_DIR}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/foo.cc
    CMAKE_FLAGS
        -DFOO=123
    COMPILE_DEFINITIONS
        -DBAZ=456
    LINK_LIBRARIES
        -lblas
    OUTPUT_VARIABLE
        compile_output
    COPY_FILE
        test_exe
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED true
)

message( "compile result <${compile_result}>" )
message( "compile_output <<
${compile_output}
>>" )

message("
--------------------------------------------------------------------------------
try_run
")

try_run(
    run_result compile_result
    ${CMAKE_CURRENT_BINARY_DIR}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/foo.cc
    CMAKE_FLAGS
        -DFOO=123
    COMPILE_DEFINITIONS
        -DBAZ=456
    LINK_LIBRARIES
        -lblas
    RUN_OUTPUT_VARIABLE
        run_output
    COMPILE_OUTPUT_VARIABLE
        compile_output
    COPY_FILE
        test_exe
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED true
)

message( "compile result <${compile_result}>" )
message( "run result <${run_result}>" )
message( "compile_output <<
${compile_output}
>>" )
message( "run_output <<
${run_output}
>>" )

message("")
