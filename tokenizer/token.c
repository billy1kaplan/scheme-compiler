#include "token.h"

void printToken(Token *token) {
    printf("%s : String", token->s);
}
void cleanupToken(Token *token) {
    free(token->s);
    free(token);
}
