#!/bin/bash

make && exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-check.txt ./vector
