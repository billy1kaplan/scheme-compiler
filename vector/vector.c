#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

// You might need other includes for printing or whatnot


/* Take an already existing Vector as a parameter. Do not create a Vector
 inside this function. Set its internal memory size to match the value given in
 the parameter, allocate an appropriately-sized C array to hold the actual data,
 and initialize the size variable to 0. */

void init(Vector *vector, int memorySize) {
    vector->array = (int *)malloc(memorySize * sizeof(int));
    vector->memorySize = memorySize;
    vector->size = 0;
}

/* Removes the array associated with the Vector. */

void cleanup(Vector *vector) {
    free(vector->array);
}

/* Print out the Vector for debugging purposes. */

void print(Vector *vector) {
    printf("[");
    for (int i=0; i < vector->size; i++) {
        printf("%i, ", vector->array[i]);
    }
    printf("]\n");
}

/* Insert value at location inside the Vector. If the list has items in
 positions 0 through n-1, you are only permitted to insert new values at
 locations 0 through n. (This is identical to Java's ArrayList behavior.) If
 there is already data at the location you are inserting into, insert slides the
 rest of the data down one position to make room for the new value. Returns 1 if
 success, and 0 if the location is invalid (less than 0, or greater than the
 size). Inserting at the very end of the current data (at position equal to
 size) is fine. All inserts should increase size by 1.

 If the internal array is too small to fit a new value, a new array of twice the
 size is created with malloc. The values are copied, the Vector is appropriately
 updated, and the old array is freed.) */

int insert(Vector *vector, int location, int value) {
    if (location < 0 || location > vector->size) {
        return 1;
    } else if (vector->size == vector->memorySize) {
        int newMemorySize = 2 * vector->memorySize;
        int* array = (int *)malloc(newMemorySize * sizeof(int));

        for (int i=location-1; i >= 0; i--) {
            array[i] = vector->array[i];
        }

        array[location] = value;

        for (int i=vector->size - 1; i >= location; i--) {
            array[i + 1] = vector->array[i];
        }

        vector->memorySize = newMemorySize;
        free(vector->array);
        vector->array = array;
        vector->size++;
        return 0;
    } else {
        for (int i=vector->size - 1; i >= location; i--) {
            vector->array[i + 1] = vector->array[i];
        }
        vector->array[location] = value;
        vector->size++;
        return 0;
    }
}

/* Obtains value at location inside the Vector. Returns 1 if success, and 0 if
 the location is invalid (less than 0, or greater than or equal to the
 size). The value itself is returned through the parameter value. */

int get(Vector *vector, int location, int *value) {
    if (location < 0 || location >= vector->size) {
        return 1;
    } else {
        *value = vector->array[location];
        return 0;
    }
}

/* Deletes value at location inside the Vector.  Returns 1 if success, and 0 if
 the location is invalid (less than 0, or greater than or equal to the
 size). When an item is deleted, everything else past it in the array should be
 slid down. The internal array itself does not need to be compressed, i.e., you
 don't need to halve it in size if it becomes half full, or anything like
 that. */
int delete(Vector *vector, int location) {
    if (location < 0 || location >= vector->size) {
        return 1;
    } else {
        // If we're at the end of the array, just decrement size
        // The final value will be ignored / overwritten.
        for (int i=location; i < vector->size - 1; i++) {
            vector->array[i] = vector->array[i + 1];
        }

        vector->size--;

        return 0;
    }
}
