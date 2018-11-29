#ifndef scheme_value_h
#define scheme_value_h

#include "common.h"
#include "parsetree.h"

//typedef double Value;
typedef ParseNode Value;

typedef struct {
  int capacity;
  int count;
  Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);
void printValue(Value value);

#endif
