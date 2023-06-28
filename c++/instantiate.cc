#include "instantiate.hh"

int main( int argc, char** argv )
{
    Matrix<float> A;
    TrapezoidMatrix<double> Tz;
    TriangularMatrix<float> Tr;

    norm( A );
    norm( Tz );
    norm( Tr );

    return 0;
}
