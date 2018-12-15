#!/usr/bin/env bash

gcc memory.c pairMemory.c operations.c value.c test_operations.c -o test

echo "Running Tests: "
./test
echo ""
echo "Tests complete"

rm test
