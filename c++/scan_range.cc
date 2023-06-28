// scan_range from TestSweeper, reimplemented using strtoll to accept
// hex (0x) and octal (0) numbers, and encode/decode base64 (64#)
// numbers as implemented in bash shell.

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

//------------------------------------------------------------------------------
// Bash shell uses 0-9, a-z, A-Z, @, _ for encoding up to base 64.
// See https://en.wikipedia.org/wiki/Base64#cite_ref-19
char const* encode_bash64_table =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@_";

// first index in row: chars where .. denotes unused chars (-1).
int decode_bash64_table[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  //   0: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  //  16: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  //  32: ..
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,  //  48: 0-9 ..
    62, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,  //  64: @ A-O
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, 63,  //  80: P-Z .. _
    -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,  //  96: .. a-o
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,  // 112: p-z ..

    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 128: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 144: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 160: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 176: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 192: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 208: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 224: ..
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  // 240: ..
};

//------------------------------------------------------------------------------
void encode_bash64( int len, char* buf, int64_t x )
{
    // 64-bit is max 11 sextets + 3 char "64#" prefix.
    assert( len >= 14 );
    buf[ 0 ] = '6';
    buf[ 1 ] = '4';
    buf[ 2 ] = '#';
    int i = 3;
    int64_t mx = 1 << 6;
    while (x >= mx && i < 11) {
        mx = mx << 6;
        ++i;
    }
    buf[ i+1 ] = '\0';
    while (x != 0) {
        int sextet = x & 0x3f;
        buf[ i ] = encode_bash64_table[ sextet ];
        x = x >> 6;
        --i;
    }
}

//------------------------------------------------------------------------------
int64_t decode_bash64( char const* buf, char** endptr, int base )
{
    long long result = 0;
    while (isspace( *buf )) {
        ++buf;
    }
    int cmp = strncmp( "64#", buf, 3 );
    if (base == 64 || (base == 0 && cmp == 0)) {
        if (cmp == 0) {
            buf += 3;  // skip "64#" prefix
        }
        while (*buf != '\0') {
            int sextet = decode_bash64_table[ int( *buf ) ];
            if (sextet == -1) {
                break;
            }
            result = (result << 6) + sextet;
            ++buf;
        }
        if (endptr) {
            *endptr = const_cast<char*>( buf );
        }
    }
    else {
        result = strtoll( buf, endptr, base );
    }
    return result;
}

//------------------------------------------------------------------------------
/// Scans for "start : stop : step"
int scan_range( char** arg, int64_t* start, int64_t* stop, int64_t* step )
{
    char* endptr = nullptr;
    int bytes, cnt;

    // Read "start". By default, stop = start and step = 1.
    *start = decode_bash64( *arg, &endptr, 0 );
    //*start = strtoll( *arg, &endptr, 0 );
    *stop  = *start;
    *step  = 1;
    if (endptr == *arg)
        return -1;  // fail
    *arg = endptr;

    // Read ":". If none found, return success (0); we read "start".
    bytes = -1;
    cnt = sscanf( *arg, " :%n", &bytes );
    if (cnt == EOF)
        return 0;
    *arg = endptr + bytes;

    // Read "stop".
    *stop = decode_bash64( *arg, &endptr, 0 );
    //*stop = strtoll( *arg, &endptr, 0 );
    if (endptr == *arg)
        return -1;  // fail
    *arg = endptr;

    // Read ":". If none found, return success (0); we read "start : stop".
    bytes = -1;
    cnt = sscanf( *arg, " :%n", &bytes );
    if (cnt == EOF)
        return 0;
    *arg = endptr + bytes;

    // Read "step".
    *step = decode_bash64( *arg, &endptr, 0 );
    //*step = strtoll( *arg, &endptr, 0 );
    if (endptr == *arg)
        return -1;  // fail
    *arg = endptr;

    // For simplicity in loops, make step non-zero where valid.
    if (*step == 0 && *start == *stop)
        *step = 1;

    // We read "start : stop : step".
    // Return success (0) unless step == 0, creating an infinite loop.
    return (*step == 0);
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    for (int i = 1; i < argc; ++i) {
        int64_t start, stop, step;
        char* arg = argv[i];
        int rc = scan_range( &arg, &start, &stop, &step );
        printf( "%d: '%-12s' => %lld : %lld : %lld, rc %d, arg %s\n",
                i, argv[i], start, stop, step, rc, arg );
        if (rc == 0) {
            assert( step != 0 );
            //printf( "   [ " );
            char buf[ 64 ];
            int64_t x;
            printf( "base64\n" );
            for (int64_t j = start; (step > 0 ? j <= stop : j >= stop); j += step) {
                encode_bash64( sizeof(buf), buf, j );
                x = decode_bash64( buf, nullptr, 0 );
                printf( "    %4lld => '%s' => %4lld\n", j, buf, x );
                assert( j == x );
            }
            printf( "hex\n" );
            for (int64_t j = start; (step > 0 ? j <= stop : j >= stop); j += step) {
                snprintf( buf, sizeof(buf), "%#llx", j );
                x = strtoll( buf, nullptr, 0 );
                printf( "    %4lld => '%s' => %4lld\n", j, buf, x );
                assert( j == x );
            }
            //printf( "]\n" );
        }
        else {
            printf( "invalid range\n\n" );
        }


        printf( "\n" );
    }

    return 0;
}
