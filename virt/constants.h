#ifndef constants_h
#define constants_h

#include "value.h"

#define ZERO INT_VALUE(0)
#define ONE INT_VALUE(1)
#define TWO INT_VALUE(2)

#define CONSTANTS_SIZE 512

typedef struct {
  Value constants[CONSTANTS_SIZE];
} ConstantsTable;

void inputConstant(int index, Value value);
Value retrieveConstant(int index);

#endif
