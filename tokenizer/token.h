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
    //Token *next;
};


typedef struct Token Token;

/* Returns an open token instance */
Token *openToken();

/* Returns a close token instance */
Token *closeToken();

Token *trueToken();
Token *falseToken();

/* Prints a human readable representation of the token including the type */
void printToken(const Token *token);

/* Cleans up the memory associated with the token */
void cleanupToken(Token *token);

#endif
