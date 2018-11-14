#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"
#include "token.h"
#include "vector.h"

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

int vectorToString(Vector *vector, char *output) {
    int errorCode = 0;

    for (int i = 0; i < vector->size; i++) {
        output[i] = vector->array[i];
    }

    return 0;
}

int tokenizeString(Vector *buffer, Token *stringToken) {
    char charRead = fgetc(stdin);
    while (charRead != EOF && charRead != '"') {
        append(buffer, charRead);
        charRead = fgetc(stdin);
    }

    int errorCode = 0;
    if ((charRead == EOF)) return 1;

    char *text = (char *)malloc(buffer->size * sizeof(char));
    printf("Test: %i, %i\n", buffer->size, strlen(text));
    if (errorCode = vectorToString(buffer, text)) return errorCode;
    stringToken->type = STR_TYPE;
    stringToken->s = text;
    return 0;
}

void tokenize() {
    Vector *buffer = (Vector *)malloc(sizeof(Vector));

    char charRead = fgetc(stdin);
    while(charRead != EOF) {
        if (charRead == '"') {
            Token *stringToken = (Token *)malloc(sizeof(Token));
            tokenizeString(buffer, stringToken);

            clear(buffer);

            printToken(stringToken);
            cleanupToken(stringToken);
        } else {
        }

        charRead = fgetc(stdin);
    }

    cleanup(buffer);
}
