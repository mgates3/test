template <typename T>
class BaseMatrix
{
};

template <typename T>
class Matrix: public BaseMatrix<T>
{
};

template <typename T>
class TrapezoidMatrix: public BaseMatrix<T>
{
};

template <typename T>
class TriangularMatrix: public TrapezoidMatrix<T>
{
};

template <typename matrix_type>
void norm( matrix_type& x );
