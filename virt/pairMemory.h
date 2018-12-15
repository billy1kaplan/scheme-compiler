#ifndef scheme_pair_memory_h
#define scheme_pair_memory_h

#include "value.h"

#define MAX_PAIRS 8192

typedef struct {
  int free;
  Value the_cars[MAX_PAIRS];
  Value the_cdrs[MAX_PAIRS];
} Memory;

void initMemory();

Value car(Value pair);
Value cdr(Value pair);
Value cons(Value first, Value second);

void displayValue(Value value);

#endif