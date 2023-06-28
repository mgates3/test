// Demonstrates using type trait with MPI. It doesn't do anything useful,
// just sends a value and receives it. This would deadlock w/o Eager.
//      mpicxx -Wall -o mpi_type mpi_type.cc

#include <mpi.h>
#include <complex>

//------------------------------------------------------------------------------
// Gives mpi_type based on actual template type T.
template <typename T>
class mpi_type {};

template<>
class mpi_type<float> {
public:
    static constexpr MPI_Datatype value = MPI_FLOAT;
};

template<>
class mpi_type<double> {
public:
    static constexpr MPI_Datatype value = MPI_DOUBLE;
};

template<>
class mpi_type< std::complex<float> > {
public:
    static constexpr MPI_Datatype value = MPI_C_COMPLEX;
};

template<>
class mpi_type< std::complex<double> > {
public:
    static constexpr MPI_Datatype value = MPI_C_DOUBLE_COMPLEX;
};


//------------------------------------------------------------------------------
template <typename T>
void sendrecv( T* data )
{
    // mpi_type<T>::value is one of MPI_FLOAT, MPI_DOUBLE, etc.
    T buf;
    MPI_Send( data, 1, mpi_type<T>::value, 0, 0, MPI_COMM_WORLD );
    MPI_Recv( &buf, 1, mpi_type<T>::value, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
}


//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    float  sx;
    double dx;
    std::complex<float>  cx;
    std::complex<double> zx;

    MPI_Init( &argc, &argv );

    sendrecv( &sx );
    sendrecv( &dx );
    sendrecv( &cx );
    sendrecv( &zx );

    MPI_Finalize();

    return 0;
}
