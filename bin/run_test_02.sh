#!/bin/bash

# Functions

test-library() {
    library=$1
    echo -n "Testing $library ... "
    if diff -y <(env LD_PRELOAD=./lib/$library ./bin/test_02 2> /dev/null) <(test-output) >& test.log; then
    	echo "success"
    else
    	echo "failure"
    	cat test.log
    	echo ""
    fi
}

test-output() {
    cat <<EOF
blocks:      1
free blocks: 1
mallocs:     6
frees:       6
callocs:     0
reallocs:    0
reuses:      2
grows:       4
shrinks:     1
splits:      1
merges:      3
requested:   6144
heap size:   3168
internal:    66.67
external:    0.00
EOF
}

# Main execution

test-library libmalloc-ff.so
test-library libmalloc-bf.so
test-library libmalloc-wf.so

# vim: sts=4 sw=4 ts=8 ft=sh
