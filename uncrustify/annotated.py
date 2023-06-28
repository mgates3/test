#!/usr/bin/env python3

import sys
import os
import re
from subprocess import run

#force = True
force = False
tests = []
failed = []

#-------------------------------------------------------------------------------
# ANSI color escape characters
# see http://en.wikipedia.org/wiki/ANSI_escape_code
esc       = chr(0x1B) + "["

bold      = esc + ";1m"
normal    = esc + "0m"

red       = esc + "31m"
green     = esc + "32m"
yellow    = esc + "33m"
blue      = esc + "34m"
magenta   = esc + "35m"
cyan      = esc + "36m"
white     = esc + "37m"

bg_red     = esc + "101m"
bg_green   = esc + "102m"
bg_yellow  = esc + "103m"
bg_blue    = esc + "104m"
bg_magenta = esc + "105m"
bg_cyan    = esc + "106m"

#-------------------------------------------------------------------------------
cfg = open( 'annotated.cfg' )

names = sys.argv[1:]
if (names):
    force = True

index = 0
block = False

for line in cfg:
    if (block):
        m = re.search( r'^#   (.*\n)', line )
        if (m):
            tests[ -1 ][ 1 ] += m.group( 1 )
            continue
        else:
            block = False

    m = re.search( r'^# (\S+):: *(.*?)(?: *// with (.*))?$', line )
    if (m):
        tests.append( list( m.groups() ) )
        if (not m.group(2)):
            block = True

    m = re.search( r'^(\w+) += .*? # (.*)', line )
    if (m):
        index += 1
        name = m.group( 1 )
        values = m.group( 2 ).split( '/' )

        if (names and name not in names):
            tests = []
            continue

        if (len( values ) == 1):
            value = values[ 0 ]
            if (value == 'unsigned number'):
                values = ['0', '1', '2', '3', '4', '5', '6', '7', '8']
            elif (value == 'number'):
                values = ['-8', '-7', '-6', '-5', '-4', '-3', '-2', '-1',
                          '0', '1', '2', '3', '4', '5', '6', '7', '8']
            elif (value == 'string'):
                #print( '%-20s is string, skipping' % (name) )
                continue
            else:
                print( 'unknown value', value )

        assert( len( values ) > 1 )

        if (len( tests ) == 0):
            #print( '%-20s: no tests, skipping' % (name) )
            continue

        print( bold + name + normal )

        infile = 'in/%03d-%s.cc' % (index, name)
        has_input = tests[ 0 ][ 0 ] == 'input'
        if (has_input):
            original = tests[ 0 ][ 1 ]
        else:
            original = '\n'.join( [ x[ 1 ] for x in tests ] ) + '\n'
        original = re.sub( r'\\n', '\n', original )
        original = re.sub( r'\\t', '\t', original )
        if (not force and os.path.exists( infile )):
            current = open( infile ).read()
            refresh = current != original
        else:
            refresh = True
        if (refresh):
            print( '    refresh' )
            f = open( infile, 'w' )
            f.write( original )
            f.close()

        for test in tests:
            value = test[ 0 ]
            if (value not in values):
                continue
            outfile = 'out/%03d-%s=%s.cc' % (index, name, value)
            if (not force and not refresh and os.path.exists( outfile )):
                #print( '    %-50s exists' % (outfile) )
                continue

            cmd = ['uncrustify', '-q', '-c', 'base.cfg',
                   '--set', name + '=' + value,
                   '-f', infile,
                   '-o', outfile]
            if (test[ 2 ]):
                t2 = re.sub( r' *= *', '=', test[ 2 ] )
                ts = re.split( ', *', t2 )
                for t in ts:
                    cmd.extend(( '--set', t ))
            # Allow lengths:
            # 30 + 10 for name + value,
            # 30 + 10 for in + name + .cc,
            # 30 + 10 + 10 for out + name + value + .cc
            # print( '    %s %s %s %s %s %-40s %s %-40s %s %-50s'
            #        % tuple( cmd[0:10] ), end='' )
            print( red + ('%-10s' % (value + ':')) + normal, *cmd, end='' )
            run( cmd )

            result = open( outfile ).read()

            if (value == 'ignore'):
                expect = original
            elif (has_input):
                expect = test[ 1 ]
            else:
                expect = (test[ 1 ] + "\n") * len( tests )
                expect = re.sub( r'\\n', '\n', expect )
                expect = re.sub( r'\\t', '\t', expect )

            if (result == expect):
                print( ' passed' )
            else:
                if (result == original):
                    msg = ' *** no change'
                else:
                    msg = ''
                print( " failed\n"
                       "result <<\n" + result + ">>" + msg + "\n"
                       "expect <<\n" + expect + ">>\n" )
                failed.append( name + '=' + value )
                os.rename( outfile, outfile + '-failed' )
        # end

        tests = []
    # end
# end

if (failed):
    print( bold + red + '\nfailed:' + normal + red + '\n' + '\n'.join( failed ) + normal )
else:
    print( bold + green + '\nall passed' + normal )
