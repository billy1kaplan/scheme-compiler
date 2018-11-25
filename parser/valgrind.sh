#!/bin/bash

tokenize() {
   exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./parser
}

tokenize_file() {
    cat $1 | tokenize
}

run_test() {
    tokenize_file $1 2>&1 | python test_script.py
}

# Run a series of test to detect leaks
make && run_test simple.txt \
    && run_test fib-tokens.txt
