#!/bin/bash

# Functions

test-library() {
    library=$1
    env LD_PRELOAD=./lib/$library cat README.md
}

# Main execution

test-library libmalloc-ff.so
test-library libmalloc-bf.so
test-library libmalloc-wf.so

# vim: sts=4 sw=4 ts=8 ft=sh
