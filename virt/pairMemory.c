#include "pairMemory.h"
#include <stdio.h>

Memory memory;

void initMemory() {
  memory.free = 0;
}

Value car(Value pair) {
  return vectorRef(memory.the_cars, pair.as.pairIndex);
}

Value cdr(Value pair) {
  return vectorRef(memory.the_cdrs, pair.as.pairIndex);
}

Value cons(Value first, Value second) {
  int currentFree = memory.free;
  vectorSet(memory.the_cars, currentFree, first);
  vectorSet(memory.the_cdrs, currentFree, second);
  memory.free = currentFree + 1;
  return PAIR_VALUE(currentFree);
}

void displayValue(Value value) {
  switch (value.type) {
  case INT:
    printf("%i", AS_INT(value));
    break;
  case PAIR:
    printf("(");
    displayValue(car(value));
    printf(" ");
    displayValue(cdr(value));
    printf(")");
    break;
  case NIL:
    printf("()");
  default:
    break;
  }
}
