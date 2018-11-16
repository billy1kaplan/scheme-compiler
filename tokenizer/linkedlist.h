#include "token.h"

struct Node  {
    Token *token;
    Node *next;
}

typedef struct Node Node;

Node create();
void cleanupLinked()
