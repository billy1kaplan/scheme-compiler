/*
  Tester program for vector.c
  By Dave Musicant
*/

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main() {
    // Create an empty vector with memory capacity of 10
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    init(vector,10);

    // Insert 50 numbers into it
    for (int i=0; i < 50; i++) {
        insert(vector,0,i);
    }

    // Display list, both in entirety as well as one by one
    print(vector);

    // Expect that the last 5 values will return status code 1
    int *value = malloc(sizeof(int));
    for (int i=0; i < vector->size + 5; i++) {
        int status = get(vector,i,value);
        printf("Status = %i, value = %i\n", status, *value);
    }
    free(value);

    // Delete a few values, and display again
    delete(vector,49);
    delete(vector,6);
    delete(vector,12);
    delete(vector,49);
    print(vector);

    // Clean up memory
    cleanup(vector);
    free(vector);

    return 0;
}
