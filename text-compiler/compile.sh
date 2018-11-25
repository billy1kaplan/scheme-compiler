#!/usr/bin/env bash

cat $1 | ./../tokenizer/tokenizer | ./../parser/parser
