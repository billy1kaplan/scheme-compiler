#!/bin/bash

make && cat sample.txt | (exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./vector)
