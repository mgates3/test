#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include <mpi.h>

//------------------------------------------------------------------------------
void random( std::vector<double>& x )
{
    for (size_t i = 0; i < x.size(); ++i) {
        x[ i ] = random() / double( RAND_MAX );
    }
}

//------------------------------------------------------------------------------
void print( const char* label, std::vector<double>& x )
{
    printf( "%s = [\n", label );
    for (size_t i = 0; i < x.size(); ++i) {
        printf( "  %7.5f", x[ i ] );
    }
    printf( "\n];\n" );
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    // Constants
    const int tag_0 = 0;

    // MPI variables
    int err = MPI_Init( &argc, &argv );
    assert( err == 0 );

    int mpi_rank;
    err = MPI_Comm_rank( MPI_COMM_WORLD, &mpi_rank );
    assert( err == 0 );

    int mpi_size;
    err = MPI_Comm_size( MPI_COMM_WORLD, &mpi_size );
    assert( err == 0 );

    // Command line arguments
    int n = 10;
    if (argc > 1)
        n = strtol( argv[1], nullptr, 0 );

    // Initial global seed.
    unsigned seed = time( nullptr );
    err = MPI_Bcast( &seed, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD );
    assert( err == 0 );
    printf( "%% rank %d global seed %x\n", mpi_rank, seed );

    // Advance seed on each rank.
    // This is not very random with a bad rand() function as on macOS:
    // it simply shifts over each rank.
    srandom( seed );
    for (int i = 0; i < mpi_rank; ++i) {
        seed = random();
    }
    if (mpi_rank > 0) {
        // xor'ing with mpi_rank helps bad rand() function.
        // seed ^= mpi_rank;
        // seed ^= mpi_rank + (mpi_rank << 8)
        //          + (mpi_rank << 16) + (mpi_rank << 24);
        printf( "%% rank %d seed %x\n", mpi_rank, seed );
        srandom( seed );
    }

    // Flush output. Hopefully that prevents mixing above output and
    // below output with multiple MPI ranks.
    fflush( 0 );
    err = MPI_Barrier( MPI_COMM_WORLD );
    assert( err == 0 );

    // Initialize data.
    std::vector<double> x( n );
    random( x );

    // Rank 0 prints for everyone.
    if (mpi_rank == 0) {
        char label[ 80 ];
        snprintf( label, sizeof(label), "x%d", mpi_rank );
        print( label, x );

        for (int src = 1; src < mpi_size; ++src) {
            MPI_Recv( x.data(), x.size(), MPI_DOUBLE, src, tag_0,
                      MPI_COMM_WORLD, MPI_STATUS_IGNORE );
            snprintf( label, sizeof(label), "x%d", src );
            print( label, x );
        }
    }
    else {

        MPI_Send( x.data(), x.size(), MPI_DOUBLE, 0, tag_0, MPI_COMM_WORLD );
    }

    // Cleanup.
    err = MPI_Finalize();
    assert( err == 0 );

    return 0;
}
