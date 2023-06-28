// Checks if class name collides with namespace names.
// Yes, case sensitive.

//--------------------
class Tile
{
public:
    Tile() {}
};


//--------------------
namespace tile {

void gemm( Tile& A, Tile& B, Tile& C ) {}

}  // namespace tile


//--------------------
// error: 'namespace Tile { }' redeclared as different kind of entity
// namespace Tile {
//
// void hemm( Tile& A, Tile& B, Tile& C );
//
// }  // namespace Tile


//--------------------
int main( int argc, char** argv )
{
    Tile A, B, C;
    tile::gemm( A, B, C );
    // Tile::hemm( A, B, C );  // error
    return 0;
}
