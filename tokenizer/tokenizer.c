#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "tokenizer.h"
#include "token.h"
#include "tokenerror.h"
#include "vector.h"

bool isWhiteSpace(char c) {
    return c == ' '
        || c == '\t'
        || c == '\n'
        || c == '\v'
        || c == '\f'
        || c == '\r'
        || c == EOF;
}

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

int vectorToInt(Vector *buffer) {
    char *stringRepr = vectorToString(buffer);
    int intRepr = atoi(stringRepr);
    free(stringRepr);
    return intRepr;
}

double vectorToDouble(Vector *buffer) {
    char *stringRepr = vectorToString(buffer);
    double doubleRepr = atof(stringRepr);
    free(stringRepr);
    return doubleRepr;
}

int tokenizeString(Vector *buffer, LinkedList *tokens, TokenError *error) {
    char charRead = fgetc(stdin);
    while (charRead != EOF && charRead != '"') {
        append(buffer, charRead);
        charRead = fgetc(stdin);
    }

    if (charRead == EOF) {
        error->message = STR_ERR;
        setDetail(error, vectorToString(buffer));
        clear(buffer);
        return 1;
    }

    Token *stringToken = (Token *)malloc(sizeof(Token));
    stringToken->type = STR_TYPE;
    stringToken->s = vectorToString(buffer);
    appendToken(tokens, stringToken);
    clear(buffer);
    return 0;
}

int tokenizeSymbol(Vector *buffer, LinkedList *tokens, TokenError *error) {
    char charRead = fgetc(stdin);
    while (!isWhiteSpace(charRead)) {
        if (charRead == ')') {
            ungetc(charRead, stdin);
            break;
        } else {
            append(buffer, charRead);
            charRead = fgetc(stdin);
        }
    }

    Token *symbolToken = (Token *)malloc(sizeof(Token));
    symbolToken->type = SYMBOL_TYPE;
    symbolToken->s = vectorToString(buffer);
    appendToken(tokens, symbolToken);
    clear(buffer);
    return 0;
}

int tokenizeDouble(Vector *buffer, LinkedList *tokens, TokenError *error) {
    char charRead = fgetc(stdin);
    while (!isWhiteSpace(charRead)) {
        append(buffer, charRead);
        if (isDigit(charRead)) {
            charRead = fgetc(stdin);
        } else if (charRead == ')') {
            ungetc(charRead, stdin);
            break;
        } else {
            return tokenizeSymbol(buffer, tokens, error);
        }
    }

    Token *doubleToken = (Token *)malloc(sizeof(Token));
    doubleToken->type = DOUBLE_TYPE;
    doubleToken->d = vectorToDouble(buffer);
    appendToken(tokens, doubleToken);
    clear(buffer);
    return 0;
}

int tokenizeBoolean(Vector *buffer, LinkedList *tokens, TokenError *error) {
    char charRead = fgetc(stdin);
    int errno = 0;
    if (charRead == 't') {
        appendToken(tokens, trueToken());
    } else if (charRead == 'f') {
        appendToken(tokens, falseToken());
    } else {
        while (!isWhiteSpace(charRead)) {
            append(buffer, charRead);
            charRead = fgetc(stdin);
        }
        error->message = BOOL_ERR;
        setDetail(error, vectorToString(buffer));
    }
    clear(buffer);
    return errno;
}

int tokenizeNumber(Vector *buffer, LinkedList *tokens, TokenError *error) {
    char charRead = fgetc(stdin);
    while (!isWhiteSpace(charRead)) {
        append(buffer, charRead);
        if (isDigit(charRead)) {
            charRead = fgetc(stdin);
        } else if (charRead == '.') {
            return tokenizeDouble(buffer, tokens, error);
        } else if (charRead == ')') {
            ungetc(charRead, stdin);
            break;
        } else {
            return tokenizeSymbol(buffer, tokens, error);
        }
    }

    Token *intToken = (Token *)malloc(sizeof(Token));
    intToken->type = INT_TYPE;
    intToken->i = vectorToInt(buffer);
    appendToken(tokens, intToken);
    clear(buffer);

    return 0;
}

void ignoreComment() {
    char charRead = fgetc(stdin);
    while (charRead != '\n' && charRead != '\r' && charRead != EOF) {
        charRead = fgetc(stdin);
    }
}

int handleMinus(Vector *buffer, LinkedList *tokens, TokenError *error) {
    char charRead = fgetc(stdin);
    append(buffer, charRead);

    charRead = fgetc(stdin);
    ungetc(charRead, stdin);
    printf("AFTER: %c, %i\n", charRead, isDigit(charRead));
    if (isDigit(charRead)) {
        return tokenizeNumber(buffer, tokens, error);
    } else {
        return tokenizeSymbol(buffer, tokens, error);
    }
}

int tokenize(LinkedList *tokens, TokenError *error) {
    Vector *buffer = (Vector *)malloc(sizeof(Vector));
    init(buffer, 8);

    int errno = 0;
    char charRead = fgetc(stdin);
    while (charRead != EOF) {
        if (isWhiteSpace(charRead)) {
            //Read and skip white space
        } else if (charRead == '-') {
            ungetc(charRead, stdin);
            errno |= handleMinus(buffer, tokens, error);
        } else if (charRead == ';') {
            ignoreComment();
        } else if (charRead == '"') {
            errno |= tokenizeString(buffer, tokens, error);
        } else if (charRead == '(') {
            appendToken(tokens, openToken());
        } else if (charRead == ')') {
            appendToken(tokens, closeToken());
        } else if (isDigit(charRead)) {
            ungetc(charRead, stdin);
            errno |= tokenizeNumber(buffer, tokens, error);
        } else if (charRead == '#') {
            errno |= tokenizeBoolean(buffer, tokens, error);
        } else {
            ungetc(charRead, stdin);
            errno |= tokenizeSymbol(buffer, tokens, error);
        }

        charRead = fgetc(stdin);
    }

    cleanup(buffer);
    return errno;
}

int handleReturn() {
    TokenError *error = (TokenError *)malloc(sizeof(TokenError));
    initError(error);

    LinkedList *tokens = malloc(sizeof(LinkedList));
    initLinkedList(tokens);

    int errno = tokenize(tokens, error);
    if (errno) {
        displayError(error);
    }  else {
        displayLinkedList(tokens);
    }
    cleanupLinkedList(tokens);
    cleanupError(error);
    return errno;
}
