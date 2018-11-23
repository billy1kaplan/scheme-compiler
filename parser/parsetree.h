#include <stdbool.h>

#ifndef _PARSETREE
#define _PARSETREE

typedef enum {INT_TYPE, DOUBLE_TYPE, STR_TYPE, BOOL_TYPE, SYMBOL_TYPE, PAIR_TYPE, NULL_TYPE} ParseNodeType;

struct ParseNode {
  ParseNodeType type;
  union {
    int i;
    double d;
    bool b;
    char *s;
    struct Pair {
      struct ParseNode *car;
      struct ParseNode *cdr;
    } consCell;
  };
};

typedef struct ParseNode ParseNode;

/* Creates a null node */
ParseNode *makeNull();

/* Constructs a pair of parse nodes */
ParseNode *cons(ParseNode *car, ParseNode *cdr);

/* returns the first element of a pair parse node */
ParseNode *car(ParseNode *parseNode);

/* returns the second element of a pair parse node */
ParseNode *cdr(ParseNode *parseNode);

/* Reverse a parse tree and all subnodes */
ParseNode *reverse(ParseNode *parseNode);

/* Returns true if all data is equal in both parse trees*/
bool equals(ParseNode *one, ParseNode *two);

/* Returns a copy of a given parse node and any possible sub-nodes */
ParseNode *copy(ParseNode *parseNode);

/* Displays the entirety of the parse tree */
void display(ParseNode *parseNode);

/* Frees memory allocated for the ParseNode */
void cleanupParseNode(ParseNode *parseNode);

#endif
