#include <stdio.h>

#include <complex>
#include <vector>
#include <array>
#include <iterator>
#include <type_traits>

//------------------------------------------------------------------------------
// define enable_if_t if not using c++14
#if __cplusplus >= 201402L
    using std::enable_if_t;
#else
    template<bool B, class T = void>
    using enable_if_t = typename std::enable_if<B, T>::type;
#endif

//------------------------------------------------------------------------------
/// Return value of scalar. Index i is ignored.
///
template <typename T>
T get(
    T v, size_t i,
    enable_if_t<std::is_arithmetic<T>::value, bool> = true )
{
    //printf( "scalar\n" );
    return v;
}

//------------------------------------------------------------------------------
/// Return value of i-th element of iterator.
///
template <typename iter_type>
typename std::iterator_traits<iter_type>::value_type
get(
    iter_type v, size_t i,
    enable_if_t<! std::is_arithmetic<iter_type>::value, bool> = true )
{
    //printf( "iterator\n" );
    return v[i];
}

#ifdef MERGED

    //------------------------------------------------------------------------------
    /// m, n, x, y can be scalars or iterators.
    /// If iterators, they must have at least as many elements as c
    /// (i.e., >= batch_count).
    /// c_first, c_last are iterators.
    /// The batch_count is std::distance( c_first, c_last ).
    ///
    template <typename m_type, typename n_type,
              typename x_type, typename y_type, typename c_type>
    void batch_func( m_type const& m, n_type const& n,
                     x_type const& x, y_type const& y,
                     c_type const& c_first, c_type const& c_last )
    {
        printf( "m_type is_arithmetic %d\n", std::is_arithmetic<m_type>::value );
        printf( "n_type is_arithmetic %d\n", std::is_arithmetic<n_type>::value );
        printf( "x_type is_arithmetic %d\n", std::is_arithmetic<x_type>::value );
        printf( "y_type is_arithmetic %d\n", std::is_arithmetic<y_type>::value );

        if (   std::is_arithmetic<m_type>::value
            && std::is_arithmetic<n_type>::value
            && std::is_arithmetic<x_type>::value
            && std::is_arithmetic<y_type>::value)
        {
            // fixed batch
            size_t batch_count = std::distance( c_first, c_last );
            printf( "m %d, n %d, x %3.1f, y %3.1f both scalars, batch_count %lu\n",
                    get(m, 0), get(n, 0), get(x, 0), get(y, 0), batch_count );
        }
        else {
            // variable batch
            size_t i = 0;
            for (auto c_iter = c_first; c_iter != c_last; ++c_iter) {
                printf( "i %lu, m %d, n %d, x %3.1f, y %3.1f, c %3.1f vector\n",
                        i, get(m, i), get(n, i), get( x, i ), get( y, i ), *c_iter );
                ++i;
            }
        }
    }

#else

    //------------------------------------------------------------------------------
    /// Fixed batched overload.
    /// m, n, x, y are all scalars.
    /// c_first, c_last are iterators.
    /// The batch_count is std::distance( c_first, c_last ).
    ///
    template <typename x_type, typename y_type, typename c_type>
    void batch_func( int m, int n,
                     x_type const& x, y_type const& y,
                     c_type const& c_first, c_type const& c_last,
                     enable_if_t< (   std::is_arithmetic<x_type>::value
                                   && std::is_arithmetic<y_type>::value), bool> = true )
    {
        size_t batch_count = std::distance( c_first, c_last );
        printf( "m %d, n %d, x %3.1f, y %3.1f both scalars, batch_count %lu\n",
                m, n, x, y, batch_count );
    }

    //------------------------------------------------------------------------------
    /// Variable batched overload.
    /// m, n, x, y can be scalars or iterators -- at least one is not a scalar.
    /// If iterators, they must have at least as many elements as c
    /// (i.e., >= batch_count).
    /// c_first, c_last are iterators.
    /// The batch_count is std::distance( c_first, c_last ).
    ///
    template <typename m_type, typename n_type,
              typename x_type, typename y_type, typename c_type>
    void batch_func( m_type const& m, n_type const& n, x_type const& x, y_type const& y,
                     c_type const& c_first, c_type const& c_last,
                     enable_if_t< ! (   std::is_arithmetic<m_type>::value
                                     && std::is_arithmetic<n_type>::value
                                     && std::is_arithmetic<x_type>::value
                                     && std::is_arithmetic<y_type>::value), bool> = true )
    {
        size_t i = 0;
        for (auto c_iter = c_first; c_iter != c_last; ++c_iter) {
            printf( "i %lu, m %d, n %d, x %3.1f, y %3.1f, c %3.1f vector\n",
                    i, get(m, i), get(n, i), get( x, i ), get( y, i ), *c_iter );
            ++i;
        }
    }

#endif

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    int n = 5;
    double x = 1.234, y = 2.345;
    std::vector<double> x_vec( n ), y_vec( n ), c( n );
    // std::array iterators are tagged as is_arithmetic.
    //std::array<int, 5>  m_vec, n_vec;
    std::vector<int>  m_vec( n ), n_vec( n );

    for (int i = 0; i < n; ++i) {
        x_vec[i] = 3.1 + 0.1*i;
        y_vec[i] = 4.1 + 0.1*i;
        c[i]     = 5.1 + 0.1*i;
        m_vec[i] = 20 + i;
        n_vec[i] = 30 + i;
    }

    printf( "----- fixed batch_func( m, n, x, y, c ... ), pass c as iterators\n" );
    batch_func( 3, 2, x, y, c.begin(), c.end() );

    printf( "\n----- fixed batch_func( m, n, x, y, &c[0] ... ), pass c as pointers\n" );
    batch_func( 3, 2, x, y, &c[0], &c[n] );

    printf( "\n----- variable batch_func( m_vec, n_vec, x, y_vec, c ... ), pass c as iterators\n" );
    batch_func( m_vec.begin(), n_vec.begin(), x, y_vec.begin(), c.begin(), c.end() );

    printf( "\n----- variable batch_func( m_vec, n_vec, x, &y[0], c ... ), pass c as iterators\n" );
    batch_func( m_vec.begin(), n_vec.begin(), x, &y_vec[0], c.begin(), c.end() );

    printf( "\n----- variable batch_func( m_vec, n_vec, x, y_vec, c ... ), pass c as iterators\n" );
    batch_func( m_vec.begin(), n_vec.begin(), x, y_vec.begin(), c.begin(), c.end() );

    printf( "\n----- variable batch_func( m_vec, n_vec, x_vec, y, c ... ), pass c as iterators\n" );
    batch_func( m_vec.begin(), n_vec.begin(), x_vec.begin(), y, c.begin(), c.end() );

    printf( "\n----- variable batch_func( m_vec, n_vec, x_vec, y_vec, c ... ), pass c as iterators\n" );
    batch_func( m_vec.begin(), n_vec.begin(), x_vec.begin(), y_vec.begin(), c.begin(), c.end() );

    printf( "\n----- variable batch_func( m, n_vec, x_vec, y_vec, c ... ), pass c as pointers\n" );
    batch_func( 11, n_vec.begin(), x_vec.begin(), y_vec.begin(), &c[0], &c[n] );

    return 0;
}
