#include "token.h"

#ifndef _LINKEDLIST
#define _LINKEDLIST

struct Node  {
    struct Node *next;
    union {
        Token *token;
        const Token *constToken;
    };
    //char *type;
    //void *data;
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
void appendToken(LinkedList *linkedList, const Token * const token);

/* Walks through the linked list and displays all contained elements */
void displayLinkedList(LinkedList *linkedList);

/* Cleans up memory associated with the linked list*/
void cleanupLinkedList(LinkedList *linkedList);

#endif
