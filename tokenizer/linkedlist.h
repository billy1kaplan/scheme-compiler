#include "token.h"
#include "tokenerror.h"

#ifndef _LINKEDLIST
#define _LINKEDLIST

struct Node  {
  struct Node *next;
  union {
    Token *token;
    TokenError *tokenError;
  };
};

typedef struct Node Node;

struct LinkedList {
  Node *head;
  Node *end;
};

typedef struct LinkedList LinkedList;

/* Makes an empty linked list */
void initLinkedList(LinkedList *linkedList);

/* Appends a given token to the end of the linked list*/
void appendToken(LinkedList *linkedList, Token *token);

/* Appends a given error to the end of the linked list*/
void appendTokenError(LinkedList *linkedList, TokenError *token);

/* Walks through the linked list and displays all contained elements */
void displayLinkedList(LinkedList *linkedList);

/* Walks through the linked list and displays all errors on stderr */
void displayTokenErrors(LinkedList *linkedList);

/* Cleans up memory associated with a normal token linked list*/
void cleanupLinkedList(LinkedList *linkedList);

/* Cleans up memory associated with an error linked list*/
void cleanupErrorList(LinkedList *linkedList);

#endif
