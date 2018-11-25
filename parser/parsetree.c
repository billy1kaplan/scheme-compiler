#include "parsetree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ParseNode NULL_NODE = { NULL_TYPE };

ParseNode *makeNull() {
  return &NULL_NODE;
}

/* Constructs a pair of parse nodes */
ParseNode *cons(ParseNode *car, ParseNode *cdr) {
  ParseNode *result = (ParseNode *)malloc(sizeof(ParseNode));
  result->type = PAIR_TYPE;
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

void setcar(ParseNode* parseNode, ParseNode *val) {
  parseNode->consCell.car = val;
}

void setcdr(ParseNode* parseNode, ParseNode *val) {
  parseNode->consCell.cdr = val;
}

ParseNode *pop(ParseNode **meta) {
  ParseNode *first = car(*meta);
  ParseNode *tmp = *meta;
  *meta = cdr(*meta);
  free(tmp);
  return first;
}


/* Reverse a parse tree and all subnodes */
ParseNode *reverse(ParseNode *parseNode) {
  ParseNode *result;
  if (parseNode->type == PAIR_TYPE) {
    result = makeNull();
    ParseNode *current = parseNode;
    while (current->type != NULL_TYPE) {
      result = cons(reverse(car(current)), result);
      current = cdr(current);
    }
  } else {
    result = copy(parseNode);
  }
  return result;
}

/* Returns true if all data is equal */
bool equals(ParseNode *one, ParseNode *two) {
  bool result;
  if (one == two) {
    result = true;
  } else if (one == NULL || two == NULL) {
    result = false;
  } else if (one->type != two->type) {
    result = false;
  } else {
    switch (one->type) {
    case NULL_TYPE:
    case STR_TYPE:
    case SYMBOL_TYPE:
      result = true;
      break;
    case PAIR_TYPE:
      result = equals(one->consCell.car, two->consCell.car)
        && equals(one->consCell.cdr, two->consCell.cdr);
      break;
    case INT_TYPE:
      result = one->i == two->i;
      break;
    case DOUBLE_TYPE:
      result = one->d == two->d;
      break;
    case BOOL_TYPE:
      result = one->b == two->b;
      break;
    }
  }

  return result;
}

/* Returns a copy of a given parse node and any possible sub-nodes */
ParseNode *copy(ParseNode *parseNode) {
  if (parseNode->type == NULL_TYPE) {
    return makeNull();
  }

  ParseNode *result = (ParseNode *)malloc(sizeof(ParseNode));
  result->type = parseNode->type;
  switch (parseNode->type) {
  case NULL_TYPE:
    break;
  case STR_TYPE:
  case SYMBOL_TYPE:
    result->s = strdup(parseNode->s);
    break;
  case PAIR_TYPE:
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

  return result;
}

void displayInternal(ParseNode *parseNode) {
  switch (parseNode->type) {
  case STR_TYPE:
  case SYMBOL_TYPE:
    printf("%s", parseNode->s);
    break;
  case PAIR_TYPE:
    printf("(");
    ParseNode *current = parseNode;
    while (current->type == PAIR_TYPE) {
      displayInternal(car(current));
      if (cdr(current)->type != NULL_TYPE) {
        printf(" ");
      }
      current = cdr(current);
    }
    printf(")");
    break;
  case INT_TYPE:
    printf("%i", parseNode->i);
    break;
  case DOUBLE_TYPE:
    printf("%f", parseNode->d);
    break;
  case BOOL_TYPE:
    printf("%i", parseNode->b);
    break;
  case NULL_TYPE:
    printf("()");
    break;
  }
}

/* Displays the entirety of the parse tree */
void display(ParseNode *parseNode) {
  ParseNode *current = parseNode;
  while (current->type == PAIR_TYPE) {
    displayInternal(car(current));
    if (cdr(current)->type != NULL_TYPE) {
      printf(" ");
    }
    current = cdr(current);
  }
}

/* Frees memory allocated for the ParseNode */
void cleanupParseNode(ParseNode *parseNode) {
  switch (parseNode->type) {
  case STR_TYPE:
  case SYMBOL_TYPE:
    free(parseNode->s);
    free(parseNode);
    break;
  case PAIR_TYPE:
    cleanupParseNode(parseNode->consCell.car);
    cleanupParseNode(parseNode->consCell.cdr);
    free(parseNode);
    break;
  case INT_TYPE:
  case DOUBLE_TYPE:
  case BOOL_TYPE:
    free(parseNode);
    break;
  case NULL_TYPE:
    break;
  }
}
