program main
    real szero;
    double precision dzero
    szero = 0
    dzero = 0
    print '(a19, "  ", e10.3, "  ", e10.3)', 'epsilon( zero )/2  ',     epsilon( szero )/2,   epsilon( dzero )/2
    print '(a19, "  ", e10.3, "  ", e10.3)', 'epsilon( zero )    ',     epsilon( szero ),     epsilon( dzero )
    print '(a19, "  ", e10.3, "  ", e10.3)', 'tiny( zero )       ',        tiny( szero ),        tiny( dzero )
    print '(a19, "  ", e10.3, "  ", e10.3)', 'huge( zero )       ',        huge( szero ),        huge( dzero )
    print '(a19, "  ", i10,   "  ", i10)',   'radix( zero )      ',       radix( szero ),       radix( dzero )
    print '(a19, "  ", i10,   "  ", i10)',   'digits( zero )     ',      digits( szero ),      digits( dzero )
    print '(a19, "  ", i10,   "  ", i10)',   'minexponent( zero )', minexponent( szero ), minexponent( dzero )
    print '(a19, "  ", i10,   "  ", i10)',   'maxexponent( zero )', maxexponent( szero ), maxexponent( dzero )
end program
