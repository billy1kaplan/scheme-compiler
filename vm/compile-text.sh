#!/usr/bin/env bash

make && cat $1 | ./../tokenizer/tokenizer | ./main
