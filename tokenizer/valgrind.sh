#!/bin/bash

#--verbose
#&& (exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./vector)

tokenize() {
   exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./vector
}

tokenize_file() {
    cat $1 | tokenize
}

#&& tokenize_file sample.txt \
#&& tokenize_file sample1.txt
#&& tokenize_file parens.txt
#&& tokenize_file parens.txt
#&& tokenize_file int1.txt \
#&& tokenize_file double1.txt \

make \
&& tokenize_file full_test1.txt
