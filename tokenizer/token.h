#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef _TOKEN
#define _TOKEN

typedef enum {INT_TYPE, DOUBLE_TYPE, STR_TYPE, BOOL_TYPE, OPEN_TYPE, CLOSE_TYPE, SYMBOL_TYPE} TokenType;

struct Token {
    TokenType type; 
    union {
        int i;
        double d;
        char *s;
        bool b;
    };
};

typedef struct Token Token;

void printToken(Token *token);
void cleanupToken(Token *token);

#endif
