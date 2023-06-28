cmake_minimum_required( VERSION 3.0 )

project( Test )

set( BLA_VENDOR "" CACHE STRING
     "Choose BLAS & LAPACK library" )

set_property(
    CACHE BLA_VENDOR PROPERTY STRINGS
    ""
    "Goto"
    "OpenBLAS"
    "FLAME"
    "ATLAS PhiPACK"
    "IBMESSL"
    "Intel10_32"
    "Intel10_64lp"
    "Intel10_64lp_seq"
    "Intel10_64ilp"
    "Intel10_64ilp_seq"
    "Intel10_64_dyn"
    "Apple"
    "Generic")

#----------------------------------------
if (DEFINED BLA_VENDOR)
    message( "BLA_VENDOR defined <${BLA_VENDOR}>" )
else()
    message( "BLA_VENDOR not defined" )
endif()
if (DEFINED CACHE{BLAS_FOUND})
    message( "BLA_VENDOR cached  <$CACHE{BLA_VENDOR}>" )
else()
    message( "BLA_VENDOR not cached" )
endif()

#----------
if (DEFINED BLAS_FOUND)
    message( "BLAS_FOUND defined <${BLAS_FOUND}>" )
else()
    message( "BLAS_FOUND not defined" )
endif()
if (DEFINED CACHE{BLAS_FOUND})
    message( "BLAS_FOUND cached  <$CACHE{BLAS_FOUND}>" )
else()
    message( "BLAS_FOUND not cached" )
endif()

#----------
if (DEFINED BLAS_LIBRARIES)
    message( "BLAS_LIBRARIES defined <${BLAS_LIBRARIES}>" )
else()
    message( "BLAS_LIBRARIES not defined" )
endif()
if (DEFINED CACHE{BLAS_LIBRARIES})
    message( "BLAS_LIBRARIES cached  <$CACHE{BLAS_LIBRARIES}>" )
else()
    message( "BLAS_LIBRARIES not cached" )
endif()

#----------
if (DEFINED BLAS_LINKER_FLAGS)
    message( "BLAS_LINKER_FLAGS defined <${BLAS_LINKER_FLAGS}>" )
else()
    message( "BLAS_LINKER_FLAGS not defined" )
endif()
if (DEFINED CACHE{BLAS_LINKER_FLAGS})
    message( "BLAS_LINKER_FLAGS cached  <$CACHE{BLAS_LINKER_FLAGS}>" )
else()
    message( "BLAS_LINKER_FLAGS not cached" )
endif()

#----------------------------------------
message( "---------------------------------------- find_package( BLAS )" )
find_package( BLAS )

#----------------------------------------
if (DEFINED BLAS_FOUND)
    message( "BLAS_FOUND defined <${BLAS_FOUND}>" )
else()
    message( "BLAS_FOUND not defined" )
endif()
if (DEFINED CACHE{BLAS_FOUND})
    message( "BLAS_FOUND cached  <$CACHE{BLAS_FOUND}>" )
else()
    message( "BLAS_FOUND not cached" )
endif()

#----------
if (DEFINED BLAS_LIBRARIES)
    message( "BLAS_LIBRARIES defined <${BLAS_LIBRARIES}>" )
else()
    message( "BLAS_LIBRARIES not defined" )
endif()
if (DEFINED CACHE{BLAS_LIBRARIES})
    message( "BLAS_LIBRARIES cached  <$CACHE{BLAS_LIBRARIES}>" )
else()
    message( "BLAS_LIBRARIES not cached" )
endif()

#----------
if (DEFINED BLAS_LINKER_FLAGS)
    message( "BLAS_LINKER_FLAGS defined <${BLAS_LINKER_FLAGS}>" )
else()
    message( "BLAS_LINKER_FLAGS not defined" )
endif()
if (DEFINED CACHE{BLAS_LINKER_FLAGS})
    message( "BLAS_LINKER_FLAGS cached  <$CACHE{BLAS_LINKER_FLAGS}>" )
else()
    message( "BLAS_LINKER_FLAGS not cached" )
endif()

add_executable( test_gemm test_gemm.cc )

target_link_libraries( test_gemm LINK_PUBLIC ${BLAS_LIBRARIES} )
