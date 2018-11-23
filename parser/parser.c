#include "parser.h"
#include "parsetree.h"
#include "vector.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

char *vectorToString(Vector *buffer) {
  char *output = (char *)malloc((buffer->size + 1) * sizeof(char));
  for (int i = 0; i < buffer->size; i++) {
    output[i] = buffer->array[i];
  }
  output[buffer->size] = '\0';
  return output;
}

int vectorToInt(Vector *buffer) {
  char *stringRepr = vectorToString(buffer);
  int intRepr = atoi(stringRepr);
  free(stringRepr);
  return intRepr;
}

double vectorToDouble(Vector *buffer) {
  char *stringRepr = vectorToString(buffer);
  double doubleRepr = atof(stringRepr);
  free(stringRepr);
  return doubleRepr;
}

bool vectorToBool(Vector *buffer) {
  char *c;
  get(buffer, 0, c);
  bool res;
  if (*c == 'f') {
    res = false;
  } else {
    res = true;
  }
  return res;
}

ParseNode *parseTreeFromAtomicToken(char type, Vector *buffer) {
  ParseNode *result = malloc(sizeof(ParseNode));
  switch (type) {
  case 'i':
    result->type = INT_TYPE;
    result->i = vectorToInt(buffer);
    break;
  case 'd':
    result->type = DOUBLE_TYPE;
    result->d = vectorToDouble(buffer);
    break;
  case 's':
    result->type = STR_TYPE;
    result->s = vectorToString(buffer);
    break;
  case 'x':
    result->type = SYMBOL_TYPE;
    result->s = vectorToString(buffer);
    break;
  case 'b':
    result->type = BOOL_TYPE;
    result->b = vectorToBool(buffer);
    break;
  default:
    // Should never hit this
    break;
  }

  return result;
}

void readToken(char *type, Vector *buffer) {
  *type = fgetc(stdin);
  fgetc(stdin);
  char charRead = fgetc(stdin);
  while (charRead != '\n' && charRead != EOF) {
    append(buffer, charRead);
    charRead = fgetc(stdin);
  }
}

ParseNode *parse() {
  ParseNode *parseTree = makeNull();

  Vector *buffer = (Vector *)malloc(sizeof(Vector));
  init(buffer, 8);
  char *type = malloc(sizeof(char));

  int depth = 0;

  readToken(type, buffer);
  while (*type != 'e') {
    if (*type == 'o') {
      parseTree = cons(makeNull(), parseTree);
    } else if (*type == 'c') {
      if (parseTree->type == PAIR_TYPE && cdr(parseTree)->type == PAIR_TYPE) {
        parseTree = cons(cons(car(parseTree), car(cdr(parseTree))),
                         cdr(cdr(parseTree)));
      }
    } else {
      ParseNode *atomicNode = parseTreeFromAtomicToken(*type, buffer);
      if (parseTree->type == PAIR_TYPE) {
        parseTree = cons(cons(atomicNode, car(parseTree)),
                         cdr(parseTree));
      } else {
        parseTree = cons(atomicNode, parseTree);
      }
    }

    clear(buffer);
    readToken(type, buffer);
  }

  free(type);
  return reverse(parseTree);
}

