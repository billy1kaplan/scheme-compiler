#include "token.h"

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
            printf("%i : Int\n", token->i);
            break;
        case DOUBLE_TYPE:
            printf("%f : Double\n", token->d);
            break;
        case STR_TYPE:
            printf("%s : String\n", token->s);
            break;
        case BOOL_TYPE:
            if (token->b) {
                printf("true : Boolean\n");
            } else {
                printf("false : Boolean\n");
            }
            break;
        case OPEN_TYPE:
            printf("( : Open\n");
            break;
        case CLOSE_TYPE:
            printf(") : Close\n");
            break;
        case SYMBOL_TYPE:
            printf("%s : Symbol\n", token->s);
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
