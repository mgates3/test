# Testing using nested classes for the ANSI color codes.
# It works, but seems more complex than needed for our purposes.
# Not really nested classes, just the parent has members that are other classes.
# But they need to point to the parent class to get enabled flag, making them
# more complex.

#-------------------------------------------------------------------------------
class Background:
    def __init__( self, top ):
        self.top = top
    
    def black( self, msg ):
        return self.top.code('20') + ' ' + msg + ' ' + self.top.end()
# end

#-------------------------------------------------------------------------------
class Foreground:
    def __init__( self, top ):
        self.top = top
    
    def black( self, msg ):
        return self.top.code('10') + ' ' + msg + ' ' + self.top.end()
# end

#-------------------------------------------------------------------------------
class Font:
    def __init__( self ):
        self.fg = Foreground( self )
        self.bg = Background( self )
        self.enabled_ = True
    
    def code( self, val ):
        if (self.enabled_):
            return 'ESC[' + val + 'm'
        else:
            return val
    
    def bold( self, msg ):
        return self.code('1') + ' ' + msg + ' ' + self.end()
    
    def italic( self, msg ):
        return self.code('2') + ' ' + msg + ' ' + self.end()
    
    def end( self ):
        return self.code('0')
# end

#-------------------------------------------------------------------------------
font = Font()

print( font.bold( 'bold' ) )
print( font.italic( 'italic' ) )
print( font.fg.black( 'fg.black' ) )
print( font.bg.black( 'bg.black' ) )
