#!/bin/sh
#
# Demonstrates difference between exporting and not exporting variables,
# depending on how sub-scripts are run (sourced vs. executed).

a=1
export b=2

echo "---- source"
source export_var_sub.sh

echo "---- dot source"
. export_var_sub.sh

echo "---- execute: $a is not exported"
./export_var_sub.sh
