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

#define IS_BOOL(value) ((ParseNode).type == BOOL_TYPE)
#define IS_INT(value) ((ParseNode).type == INT_TYPE)
#define IS_DOUBLE(value) ((ParseNode).type == DOUBLE_TYPE)
#define IS_NULL(value) ((ParseNode).type == NULL_TYPE)

#define BOOL_NODE(value) ((ParseNode) { BOOL_TYPE, .b = value})
#define INT_NODE(value) ((ParseNode) { INT_TYPE, .i = value})
#define DOUBLE_NODE(value) ((ParseNode) { DOUBLE_TYPE, .d = value})

#define AS_BOOL(value) ((value).b)
#define AS_INT(value) ((value).i)
#define AS_DOUBLE(value) ((value).d)

typedef struct ParseNode ParseNode;

/* Creates a null node */
ParseNode *makeNull();

/* Constructs a pair of parse nodes */
ParseNode *cons(ParseNode *car, ParseNode *cdr);

/* returns the first element of a pair parse node */
ParseNode *car(ParseNode *parseNode);

/* returns the second element of a pair parse node */
ParseNode *cdr(ParseNode *parseNode);

/* Modifies the car element of the given pair */
void setcar(ParseNode* parseNode, ParseNode *val);

/* Modifies the cdr element of the given pair */
void setcdr(ParseNode* parseNode, ParseNode *val);

/* Returns the first element of the pair and assigns the pair to the
   cdr value */
ParseNode *popNode(ParseNode **meta);

/* Reverses a parse tree to depth 1 */
ParseNode *reverseOne(ParseNode *parseNode);

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
