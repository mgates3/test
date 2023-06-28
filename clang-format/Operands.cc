int main( int argc, char** argv )
{
    int x = 1 + 2 + 3;

    int y = blas::norm(long_function_arguments, long_long) +
            blas::norm(long_function_arguments, long_long) +
            blas::norm(long_function_arguments, long_long);

    int y = blas::norm(long_function_arguments, long_long)
             + blas::norm(long_function_arguments, long_long)
                + blas::norm(long_function_arguments, long_long);
}
