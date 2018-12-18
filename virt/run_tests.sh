#!/usr/bin/env bash

echo "Running Tests: "
gcc memory.c pairMemory.c operations.c value.c test_operations.c -o test
./test
rm test

gcc memory.c pairMemory.c value.c symboltable.c testsymboltable.c -o test
./test
rm test

gcc memory.c pairMemory.c value.c environment.c testenv.c -o test
./test
rm test
echo ""
echo "Tests complete"
