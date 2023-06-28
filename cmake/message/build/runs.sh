#!/bin/tcsh

cmake --log-level=ERROR   .. >&! log-0-error.txt
cmake --log-level=WARNING .. >&! log-1-warning.txt
cmake --log-level=NOTICE  .. >&! log-2-notice.txt
cmake --log-level=STATUS  .. >&! log-3-status.txt
cmake                     .. >&! log-3-default.txt
cmake --log-level=VERBOSE .. >&! log-4-verbose.txt
cmake --log-level=DEBUG   .. >&! log-5-debug.txt
cmake --log-level=TRACE   .. >&! log-6-trace.txt
