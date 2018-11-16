#include "linkedlist.h"

#include <stdlib.h>

/* Makes an empty linked list */
void initLinkedList(LinkedList *linkedList) {
    linkedList->head = NULL;
    linkedList->end = NULL;
}

/* Appends a given token to the end of the linked list*/
void appendToken(LinkedList *linkedList, const Token *token) {
    Node *newNode = malloc(sizeof(Node));

    newNode->constToken = token;

    newNode->next = NULL;

    if (linkedList->end != NULL) {
        Node *endNode = linkedList->end;
        endNode->next = newNode;
    } else {
        linkedList->head = newNode;
    }

    linkedList->end = newNode;
}

/* Walks through the linked list and displays all contained elements */
void displayLinkedList(LinkedList *linkedList) {
    Node *current = linkedList->head;

    while (current != NULL) {
        printToken(current->token);
        current = current->next;
    }
}

/* Cleans up memory associated with the linked list*/
void cleanupLinkedList(LinkedList *linkedList) {
    Node *current = linkedList->head;

    while (current != NULL) {
        Node *prev = current;
        current = current->next;

        cleanupToken(prev->token);
        free(prev);
    }

    free(linkedList);
}
