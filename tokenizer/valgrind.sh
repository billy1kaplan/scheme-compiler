#!/bin/bash

#--verbose

make \
&& cat sample.txt | (exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./vector) \
&& cat sample1.txt | (exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./vector)
