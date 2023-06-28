#!/bin/sh

set -x

# Suppress trace output of `echo` commands.
# https://superuser.com/a/1141026
echo_and_restore() {
    builtin echo "$*"
    case "$save_flags" in
        (*x*)  set -x
    esac
}
alias echo='{ save_flags="$-"; set +x; } 2> /dev/null; echo_and_restore'

# Suppress trace output of commands executed with `run`. Useful for Spack.
run() {
    { set +x; } 2> /dev/null;
    $@;
    set -x
}

# Alias doesn't work.
alias run_alias='{ save_flags="$-"; set +x; } 2> /dev/null; $@; set -x'

echo "================================================================================"

module avail

echo "================================================================================"

run module avail

echo "================================================================================"

run_alias module avail

echo "================================================================================"
