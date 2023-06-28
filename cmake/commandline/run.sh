#!/bin/sh
#
# Test defining flags on cmake commandline. See
# https://stackoverflow.com/questions/8564337/how-to-define-a-c-preprocessor-macro-through-the-command-line-with-cmake

set -v  # verbose

echo "============================================================"
mkdir build-0
cd build-0
cmake ..
make
./main
cd ..


echo "============================================================"
mkdir build-1
cd build-1
cmake -DCMAKE_CXX_FLAGS='-DMAGMA_ILP64' ..
make
./main
cd ..


echo "============================================================"
mkdir build-2
cd build-2
cmake -DCMAKE_CXX_FLAGS='-DMAGMA_ILP64 -DMKL_ILP64' ..
make
./main
cd ..

set +v  # verbose off
