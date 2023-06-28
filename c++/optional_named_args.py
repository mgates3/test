def foo(a, b=1, c=2, d=3):
    print( a, b, c, d )

foo( 1 )
foo( 1, 5, 6, 7 )
foo( 1, b=9 )
foo( 1, c=9 )
