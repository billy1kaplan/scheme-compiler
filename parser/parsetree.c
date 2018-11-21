#include "parsetree.h"

#include <stdlib.h>
#include <string.h>


/* Constructs a pair of parse nodes */
ParseNode *cons(ParseNode *car, ParseNode *cdr) {
  ParseNode *result = (ParseNode *)malloc(sizeof(ParseNode));
  result->type = PAIR;
  result->consCell.car = car;
  result->consCell.cdr = cdr;
  return result;
}

/* returns the first element of a pair parse node */
ParseNode *car(ParseNode *parseNode) {
  return parseNode->consCell.car;
}

/* returns the second element of a pair parse node */
ParseNode *cdr(ParseNode *parseNode) {
  return parseNode->consCell.cdr;
}

/* Reverse a parse tree and all subnodes */
ParseNode *reverse(ParseNode *parseNode) {
  ParseNode *result;
  if (parseNode != NULL) {
    if (parseNode->type == PAIR) {
      result = cons(reverse(copy(parseNode->consCell.cdr)),
                    reverse(copy(parseNode->consCell.car)));
    } else {
      result = copy(parseNode);
    }
  } else {
    result = NULL;
  }

  return result;
}

/* Returns true if all data is equal */
bool *equals(ParseNode *one, ParseNode *two) {
  bool result;
  if (one == two) {
    result = true;
  } else if (one == NULL || two == NULL) {
    result = false;
  } else {
    switch (parseNode->type) {
    case STR_TYPE:
    case SYMBOL_TYPE:
      result = true;
      break;
    case PAIR:
      result = equals(parseNode->consCell.car)
        && equals(parseNode->consCell.cdr);
      break;
    case INT_TYPE:
      result = parseNode
    case DOUBLE_TYPE:
    case BOOL_TYPE:
      break;
    }
  }

  return result
    }

/* Returns a copy of a given parse node and any possible sub-nodes */
ParseNode *copy(ParseNode *parseNode) {
  ParseNode *result;
  if (parseNode != NULL) {
    result = (ParseNode *)malloc(sizeof(ParseNode));
    result->type = parseNode->type;

    switch (parseNode->type) {
    case STR_TYPE:
    case SYMBOL_TYPE:
      result->s = malloc(sizeof(char));
      break;
    case PAIR:
      result->consCell.car = copy(parseNode->consCell.car);
      result->consCell.cdr = copy(parseNode->consCell.cdr);
      break;
    case INT_TYPE:
      result->i = parseNode->i;
      break;
    case DOUBLE_TYPE:
      result->d = parseNode->d;
      break;
    case BOOL_TYPE:
      result->b = parseNode->b;
      break;
    }
  } else {
    result = NULL;
  }

  return result;
}

/* Frees memory allocated for the ParseNode */
void cleanupParseNode(ParseNode *parseNode) {
  if (parseNode != NULL) {
    switch (parseNode->type) {
    case STR_TYPE:
    case SYMBOL_TYPE:
      free(parseNode->s);
    case PAIR:
      free(parseNode->consCell.car);
      free(parseNode->consCell.cdr);
    case INT_TYPE:
    case DOUBLE_TYPE:
    case BOOL_TYPE:
      break;
    }

    free(parseNode);
  }
}
