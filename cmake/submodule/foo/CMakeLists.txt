cmake_minimum_required( VERSION 3.15 )

message( "******************** project foo" )
project(
    foo
    VERSION 1.0
    LANGUAGES CXX
)

add_library(
    foo
    src/foo.cc
)

# Include directory.
# During build it's {source}/include; after install it's {prefix}/include.
target_include_directories(
    foo
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
)

# Use and export -std=c++11; don't allow -std=gnu++11 extensions.
target_compile_features( foo PUBLIC cxx_std_11 )
set_target_properties( foo PROPERTIES CXX_EXTENSIONS false )

# Conditionally add -Wall. See CMake tutorial.
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.15)
    set( gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>" )
    target_compile_options(
        foo PRIVATE "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall>>" )
endif()


#-------------------------------------------------------------------------------
# Install files

# GNU Filesystem Conventions
include( GNUInstallDirs )
set( INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/foo )

# Install library and add to <package>Targets.cmake
install(
    TARGETS foo
    EXPORT fooTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}  # no default before 3.14
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install header files
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/    # / copies contents, not directory itself
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING REGEX "\\.(h|hh)$"
)

# Install <package>Targets.cmake
install(
    EXPORT fooTargets
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Also export <package>Targets.cmake in build directory
export(
    EXPORT fooTargets
    FILE "fooTargets.cmake"
)

# Install <package>Config.cmake and <package>ConfigVersion.cmake,
# to enable find_package( <package> ).
include( CMakePackageConfigHelpers )
configure_package_config_file(
    "fooConfig.cmake.in"
    "fooConfig.cmake"
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)
write_basic_package_version_file(
    "fooConfigVersion.cmake"
    VERSION "${foo_VERSION}"
    COMPATIBILITY AnyNewerVersion
)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/fooConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/fooConfigVersion.cmake"
    DESTINATION ${INSTALL_CONFIGDIR}
)
