#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"
#include "token.h"
#include "tokenerror.h"
#include "vector.h"

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

char *vectorToString(Vector *buffer) {
    char *output = (char *)malloc((buffer->size + 1) * sizeof(char));
    for (int i = 0; i < buffer->size; i++) {
        output[i] = buffer->array[i];
    }
    output[buffer->size] = '\0';
    return output;
}

int tokenizeString(Vector *buffer, Token *stringToken, TokenError *error) {
    char charRead = fgetc(stdin);
    while (charRead != EOF && charRead != '"') {
        append(buffer, charRead);
        charRead = fgetc(stdin);
    }

    if (charRead == EOF) {
        error->message = STR_ERR;
        setDetail(error, vectorToString(buffer));
        return 22;
    }

    stringToken->type = STR_TYPE;
    stringToken->s = vectorToString(buffer);
    return 0;
}

int tokenize(TokenError *error) {
    Vector *buffer = (Vector *)malloc(sizeof(Vector));
    init(buffer, 8);

    int errno = 0;
    char charRead = fgetc(stdin);
    while (charRead != EOF) {
        if (charRead == '"') {
            Token *stringToken = (Token *)malloc(sizeof(Token));
            if ((errno = tokenizeString(buffer, stringToken, error))) {
                free(stringToken);
                cleanup(buffer);
                return errno;
            }

            printToken(stringToken);

            clear(buffer);
            cleanupToken(stringToken);
        } else {
        }

        charRead = fgetc(stdin);
    }

    cleanup(buffer);
    return 0;
}

int handleReturn() {
    TokenError *error = (TokenError *)malloc(sizeof(TokenError));
    initError(error);

    int errno = tokenize(error);
    if (errno) {
        displayError(error);
    } 
    cleanupError(error);
    return errno;
}
