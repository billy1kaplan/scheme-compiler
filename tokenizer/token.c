#include "token.h"

#include <stdlib.h>
#include <stdio.h>

Token OPEN_CONST = { OPEN_TYPE };
Token CLOSE_CONST = { CLOSE_TYPE };

Token TRUE_CONST = { BOOL_TYPE, .b=true };
Token FALSE_CONST = { BOOL_TYPE, .b=false };

Token *openToken() {
    return &OPEN_CONST;
}

Token *closeToken() {
    return &CLOSE_CONST;
}

Token *trueToken() {
    return &TRUE_CONST;
}

Token *falseToken() {
    return &FALSE_CONST;
}

void printToken(const Token *token) {
    switch (token->type) {
        case INT_TYPE:
            printf("i:%i\n", token->i);
            break;
        case DOUBLE_TYPE:
            printf("d:%f\n", token->d);
            break;
        case STR_TYPE:
            printf("s:%s\n", token->s);
            break;
        case BOOL_TYPE:
            if (token->b) {
                printf("b:true\n");
            } else {
                printf("b:false\n");
            }
            break;
        case OPEN_TYPE:
            printf("o:(\n");
            break;
        case CLOSE_TYPE:
            printf("c:)\n");
            break;
        case SYMBOL_TYPE:
            printf("x:%s\n", token->s);
            break;
    }
}

void cleanupToken(Token *token) {
    switch (token->type) {
        case SYMBOL_TYPE:
        case STR_TYPE:
            free(token->s);
            free(token);
            break;
        case BOOL_TYPE:
        case OPEN_TYPE:
        case CLOSE_TYPE:
            break;
        case INT_TYPE:
        case DOUBLE_TYPE:
            free(token);
            break;
    }
}
