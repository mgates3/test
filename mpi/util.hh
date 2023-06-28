#ifndef MPI_UTIL_HH
#define MPI_UTIL_HH

#include <stdio.h>
#include <mpi.h>
#include <stdexcept>
#include <vector>

//------------------------------------------------------------------------------
/// [internal] Throws std::runtime_error on MPI errors.
/// Use via mpi_call macro.
///
void mpi_call_( int err, const char* str, const char* file, int line )
{
    if (err != MPI_SUCCESS) {
        char errstr[ MPI_MAX_ERROR_STRING ];
        char msg[ 1024 ];
        int len = 0;
        int err2 = MPI_Error_string( err, errstr, &len );
        len = snprintf( msg, sizeof(msg), "MPI error: %s (%d)in `%s` at %s:%d.\n",
                        errstr, err, str, file, line );
        if (err2 != MPI_SUCCESS) {
            len += snprintf(
                       msg + len, sizeof(msg) - len,
                       "Also, MPI_Error_string returned error %d.\n", err2 );
        }
        throw std::runtime_error( msg );
    }
}

/// Throws std::runtime_error on MPI errors.
#define mpi_call( error ) \
        mpi_call_( error, #error, __FILE__, __LINE__ )

//------------------------------------------------------------------------------
int snprintf_value( char* buf, int len, double value )
{
    return snprintf( buf, len, " %5.1f", value );
}

//------------------------------------------------------------------------------
int snprintf_value( char* buf, int len, int value )
{
    return snprintf( buf, len, " %5d", value );
}

//------------------------------------------------------------------------------
int snprintf_value( char* buf, int len, int64_t value )
{
    using llong = long long;
    return snprintf( buf, len, " %5lld", llong( value ) );
}

//------------------------------------------------------------------------------
template <typename T>
std::string to_string( std::vector<T>& x )
{
    int n = x.size();
    int len = n*6 + 1;
    char* str = (char*) malloc( len * sizeof(char) );
    int used = 0;
    for (int i = 0; i < n; ++i) {
        used += snprintf_value( str + used, len - used, x[ i ] );
    }
    return std::string( str );
}

#endif  // MPI_UTIL_HH
