#include <stdio.h>
#include <stdlib.h>

#include "parsetree.h"

void assertEquals(char *msg, void *expected, void *actual) {
  if (expected != actual) {
    printf("Failed test: %s\n", msg);
  }
}

void assertEqualTree(char *msg, ParseNode *one, ParseNode *two) {
  if (!equals(one, two)) {
    printf("Failed test: %s\n", msg);
  }
}

void testCons() {
  ParseNode *nodeOne = (ParseNode *)malloc(sizeof(ParseNode));
  ParseNode *nodeTwo = (ParseNode *)malloc(sizeof(ParseNode));

  ParseNode *consNode = cons(nodeOne, nodeTwo);

  assertEquals("Car of cons is item one", nodeOne, car(consNode));
  assertEquals("Cdr of cons is item two", nodeTwo, cdr(consNode));
}

void testEquals() {
  ParseNode *nodeOne = (ParseNode *)malloc(sizeof(ParseNode));
  nodeOne->type = INT_TYPE;
  nodeOne->i = 5;

  ParseNode *nodeTwo = (ParseNode *)malloc(sizeof(ParseNode));
  nodeTwo->type = INT_TYPE;
  nodeTwo->i = 5;

  assertEqualTree("Value of integer nodes are equal", nodeOne, nodeTwo);
}

void testEqualsReflexive() {
  ParseNode *nodeOne = (ParseNode *)malloc(sizeof(ParseNode));
  nodeOne->type = INT_TYPE;
  nodeOne->i = 5;

  assertEqualTree("Assert a node equals itself", nodeOne, nodeOne);
}

void testCopy() {
  ParseNode *nodeOne = (ParseNode *)malloc(sizeof(ParseNode));
  nodeOne->type = INT_TYPE;
  nodeOne->i = 5;

  assertEqualTree("Copy of Item", nodeOne, copy(nodeOne));
}

void testReverse() {
  ParseNode *nodeOne = (ParseNode *)malloc(sizeof(ParseNode));
  nodeOne->type = INT_TYPE;
  nodeOne->i = 5;

  ParseNode *nodeTwo = (ParseNode *)malloc(sizeof(ParseNode));

  ParseNode *consNode = cons(nodeOne, nodeTwo);
  consNode = reverse(consNode);

  assertEqualTree("Reverse car of cons is item two", nodeTwo, car(consNode));
  assertEqualTree("Reverse cdr of cons is item one", nodeOne, cdr(consNode));
}

void testCleanUp() {
  ParseNode *nodeOne = (ParseNode *)malloc(sizeof(ParseNode));
  ParseNode *nodeTwo = (ParseNode *)malloc(sizeof(ParseNode));

  ParseNode *consNode = cons(nodeOne, nodeTwo);
  cleanupParseNode(consNode);
}

int main() {
  printf("Running tests...\n");
  testCons();
  testEquals();
  testEqualsReflexive();
  testCopy();
  testReverse();
  testCleanUp();
  printf("Tests complete\n");
}
