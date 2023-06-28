#include <stdio.h>
#include <limits>
#include <cfloat>  // float.h
#include <cmath>   // math.h

//------------------------------------------------------------------------------
#define FORTRAN_NAME(lower, upper) lower##_

#define lapack_slamch FORTRAN_NAME(slamch, SLAMCH)
extern "C"
float lapack_slamch( const char* cmach );

#define lapack_dlamch FORTRAN_NAME(dlamch, DLAMCH)
extern "C"
double lapack_dlamch( const char* cmach );

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    // Check that these are equivalent.
    // Their definition isn't (safe min is where 1/x doesn't overflow),
    // but their numerical value is the same.
    // printf( "sfmin = dlamch('s')                = %.16e\n", lapack_dlamch("s") );
    // printf( "std::numeric_limits<double>::min() = %.16e, same %d\n", std::numeric_limits<double>::min(),
    //         lapack_dlamch("s") == std::numeric_limits<double>::min() );
    //
    // printf( "sfmin = slamch('s')                = %.16e\n", lapack_slamch("s") );
    // printf( "std::numeric_limits<float>::min()  = %.16e, same %d\n", std::numeric_limits<float>::min(),
    //         lapack_slamch("s") == std::numeric_limits<float>::min() );

    const char* hr =
    "---------------------------------------------------------------+"
    "--------------------------------------+"
    "--------------------------------------+---------";

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10s  %10s  |  %10s  %10s  %10s  |  %s\n",
            "LAPACK", "C", "C++", "Fortran",
            "LAPACK", "C", "C++",
            "LAPACK", "C", "C++", "notes" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10s  %10s  |  %10s  %10s  %10s  |\n",
            "lamch", "macro", "numeric_limits", "intrinsic",
            "single", "single", "single",
            "double", "double", "double" );

    //-------------------- epsilon
    printf( "%s\n", hr );
    // or epsilon / base.
    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.2e  %10.2e  %10.2e  |  %10.2e  %10.2e  %10.2e  |  %s\n",
            "e: eps", "FLT_EPSILON/2", "epsilon()/2", "epsilon(z)/2",
            lapack_slamch("e"), FLT_EPSILON/2, std::numeric_limits<float >::epsilon()/2,
            lapack_dlamch("e"), DBL_EPSILON/2, std::numeric_limits<double>::epsilon()/2,
            "Higham: u unit roundoff, Heath: eps_mach" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.2e  %10.2e  %10.2e  |  %10.2e  %10.2e  %10.2e  |  %s\n",
            "p: eps*base", "FLT_EPSILON", "epsilon()", "epsilon(z)",
            lapack_slamch("p"), FLT_EPSILON, std::numeric_limits<float >::epsilon(),
            lapack_dlamch("p"), DBL_EPSILON, std::numeric_limits<double>::epsilon(),
            "Matlab: eps; ulp" );

    //-------------------- min, max
    printf( "%s\n", hr );
    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.2e  %10s  %10s  |  %10.2e  %10s  %10s  |  %s\n",
            "s: sfmin", "--", "--", "--",
            lapack_slamch("s"), "--", "--",
            lapack_dlamch("s"), "--", "--",
            "1/sfmin doesn't overflow" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.2e  %10.2e  %10.2e  |  %10.2e  %10.2e  %10.2e  |  %s\n",
            "u: rmin", "FLT_MIN", "min()", "tiny(z)",
            lapack_slamch("u"), FLT_MIN, std::numeric_limits<float >::min(),
            lapack_dlamch("u"), DBL_MIN, std::numeric_limits<double>::min(),
             "underflow (UFL)" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10s  %10.2e  |  %10s  %10s  %10.2e  |\n",
            "--", "--", "denorm_min()", "--",
            "--", "--", std::numeric_limits<float >::denorm_min(),
            "--", "--", std::numeric_limits<double>::denorm_min() );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.2e  %10.2e  %10.2e  |  %10.2e  %10.2e  %10.2e  |  %s\n",
            "o: rmax", "FLT_MAX", "max()", "huge(z)",
            lapack_slamch("o"), FLT_MAX, std::numeric_limits<float>::max(),
            lapack_dlamch("o"), DBL_MAX, std::numeric_limits<double>::max(),
             "overflow (OFL)" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10s  %10.2e  |  %10s  %10s  %10.2e  |\n",
            "--", "--", "lowest()", "--",
            "--", "--", std::numeric_limits<float>::lowest(),
            "--", "--", std::numeric_limits<double>::lowest() );

    //-------------------- infinity, nan
    printf( "%s\n", hr );
    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10.2e  %10.2e  |  %10s  %10.2e  %10.2e  |  %s\n",
            "--", "HUGE_VALF", "infinity()", "--",
            "--", HUGE_VALF, std::numeric_limits<float>::infinity(),
            "--", HUGE_VAL,  std::numeric_limits<double>::infinity(),
            "or C's INFINITY" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10.2e  %10.2e  |  %10s  %10.2e  %10.2e  |\n",
            "--", "nanf(\"\")", "quiet_NaN()", "--",
            "--", nanf(""), std::numeric_limits<float>::quiet_NaN(),
            "--", nan(""),  std::numeric_limits<double>::quiet_NaN() );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10s  %10.2e  |  %10s  %10s  %10.2e  |\n",
            "--", "--", "signaling_NaN()", "--",
            "--", "--", std::numeric_limits<float>::signaling_NaN(),
            "--", "--", std::numeric_limits<double>::signaling_NaN() );

    //-------------------- radix, digits, exponent
    printf( "%s\n", hr );
    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.0f  %10d  %10d  |  %10.0f  %10s  %10d  |\n",
            "b: base", "FLT_RADIX", "radix", "radix(z)",
            lapack_slamch("b"), FLT_RADIX, std::numeric_limits<float>::radix,
            lapack_dlamch("b"), "--",      std::numeric_limits<double>::radix );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.0f  %10d  %10d  |  %10.0f  %10d  %10d  |  %s\n",
            "n: digits", "FLT_MANT_DIG", "digits", "digits(z)",
            lapack_slamch("n"), FLT_MANT_DIG, std::numeric_limits<float >::digits,
            lapack_dlamch("n"), DBL_MANT_DIG, std::numeric_limits<double>::digits,
            "mantissa base-2 bits" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10d  %10d  |  %10s  %10d  %10d  |  %s\n",
            "--", "FLT_DIG", "digits10", "--",
            "--", FLT_DIG, std::numeric_limits<float >::digits10,
            "--", DBL_DIG, std::numeric_limits<double>::digits10,
            "mantissa base-10 digits (min.)" );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10s  %10d  |  %10s  %10s  %10d  |\n",
            "--", "--", "max_digits10", "--",
            "--", "--", std::numeric_limits<float >::max_digits10,
            "--", "--", std::numeric_limits<double>::max_digits10 );

    printf( "%-11s  %-14s  %-16s  %-14s  |      2^%4.0f      2^%4d      2^%4d  |     2^%5.0f     2^%5d     2^%5d  |\n",
            "m: emin", "FLT_MIN_EXP", "min_exponent()", "minexponent(z)",
            lapack_slamch("m"), FLT_MIN_EXP, std::numeric_limits<float >::min_exponent,
            lapack_dlamch("m"), DBL_MIN_EXP, std::numeric_limits<double>::min_exponent );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s      10^%3d      10^%3d  |  %10s     10^%4d     10^%4d  |\n",
            "--", "FLT_MIN_10_EXP", "min_exponent10()", "--",
            "--", FLT_MIN_10_EXP, std::numeric_limits<float >::min_exponent10,
            "--", DBL_MIN_10_EXP, std::numeric_limits<double>::min_exponent10 );

    printf( "%-11s  %-14s  %-16s  %-14s  |       2^%3.0f       2^%3d       2^%3d  |      2^%4.0f      2^%4d      2^%4d  |\n",
            "l: emax", "FLT_MAX_EXP", "max_exponent()", "maxexponent(z)",
            lapack_slamch("l"), FLT_MAX_EXP, std::numeric_limits<float >::max_exponent,
            lapack_dlamch("l"), DBL_MAX_EXP, std::numeric_limits<double>::max_exponent );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s       10^%2d       10^%2d  |  %10s      10^%3d      10^%3d  |\n",
            "--", "FLT_MAX_10_EXP", "max_exponent10()", "--",
            "--", FLT_MAX_10_EXP, std::numeric_limits<float >::max_exponent10,
            "--", DBL_MAX_10_EXP, std::numeric_limits<double>::max_exponent10 );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10.0f  %10d  %10d  |  %10.0f  %10s  %10d  |\n",
            "r: rnd", "FLT_ROUNDS", "round_style", "--",
            lapack_slamch("r"), FLT_ROUNDS, std::numeric_limits<float >::round_style,
            lapack_dlamch("r"), "--",       std::numeric_limits<double>::round_style );

    printf( "%-11s  %-14s  %-16s  %-14s  |  %10s  %10s  %10.2f  |  %10s  %10s  %10.2f  |\n",
            "--", "--", "round_error()", "--",
            "--", "--", std::numeric_limits<float >::round_error(),
            "--", "--", std::numeric_limits<double>::round_error() );

    //-------------------- notes
    printf( "%s\n", hr );
    printf( "\n"
            "LAPACK uses slamch for float, dlamch for double.\n"
            "C uses prefix FLT_ for float and DBL_ for double,\n"
            "  or suffix f or F for float (nanf), no suffix for double (nan).\n"
            "C++ uses given functions and values in std::numeric_limits<T>::...\n"
            "Fortran: z = zero\n" );


    double derror1 = lapack_dlamch("s") - lapack_dlamch("u");
    double derror2 = lapack_dlamch("s") - std::numeric_limits<double>::min();
    printf( "safe min %.8e - rmin %.8e = %.8e\n", lapack_dlamch("s"), lapack_dlamch("u"), derror1 );
    printf( "safe min %.8e - min  %.8e = %.8e\n", lapack_dlamch("s"), std::numeric_limits<double>::min(), derror2 );

    return 0;
}
