#!/bin/bash

tokenize() {
   exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./vector
}

tokenize_file() {
    cat $1 | tokenize
}

run_test() {
    tokenize_file $1 2>&1 | python test_script.py
}

 Run a series of test to detect leaks
make && run_test hard-scheme.txt \
    && run_test parens.txt \
    && run_test numbers.txt \
    && run_test strings-symbols.txt \
    && run_test strings.txt \
    && run_test booleans.txt \
    && run_test errors.txt
