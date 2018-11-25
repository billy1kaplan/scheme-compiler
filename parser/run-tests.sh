#!/usr/bin/env bash

parse_file() {
    cat $1 | ./parser
}

make && parse_file open-parens.txt \
         && parse_file closed-parens.txt \
         && parse_file simple.txt \
         && parse_file fib-tokens.txt
