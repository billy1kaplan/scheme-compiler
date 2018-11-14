#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "tokenizer.h"

int vectorToString(Vector *vector, char *output) {
    int errorCode = 0;

    for (int i = 0; i < vector->size; i++) {
        output[i] = vector->array[i];
    }

    return 0;
}

int main() {
    Vector *testVector = (Vector *)malloc(sizeof(Vector));
    init(testVector, 5);

    for (char i = 48; i < 60; i++) {
        append(testVector, i);
    }

    char *t = (char *)malloc(sizeof(char) * testVector->size);
    vectorToString(testVector, t);
    free(t);

    print(testVector);

    cleanup(testVector);

    //tokenize();
}
