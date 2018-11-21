#include "linkedlist.h"

#include <stdlib.h>

/* Makes an empty linked list */
void initLinkedList(LinkedList *linkedList) {
  linkedList->head = NULL;
  linkedList->end = NULL;
}

/* Appends a given token to the end of the linked list*/
void appendToken(LinkedList *linkedList, Token *token) {
  Node *newNode = malloc(sizeof(Node));

  newNode->token = token;

  newNode->next = NULL;

  if (linkedList->end != NULL) {
    Node *endNode = linkedList->end;
    endNode->next = newNode;
  } else {
    linkedList->head = newNode;
  }

  linkedList->end = newNode;
}

/* Appends a given error to the end of the linked list*/
void appendTokenError(LinkedList *linkedList, TokenError *tokenError) {
  Node *newNode = malloc(sizeof(Node));

  newNode->tokenError = tokenError;

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

/* Walks through the linked list and displays all errors on stderr */
void displayTokenErrors(LinkedList *linkedList) {
  Node *current = linkedList->head;

  while (current != NULL) {
    displayError(current->tokenError);
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

/* Cleans up memory associated with an error linked list*/
void cleanupErrorList(LinkedList *linkedList) {
  Node *current = linkedList->head;

  while (current != NULL) {
    Node *prev = current;
    current = current->next;

    cleanupError(prev->tokenError);
    free(prev);
  }

  free(linkedList);
}
