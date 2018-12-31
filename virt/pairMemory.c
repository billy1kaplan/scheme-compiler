#include <stdio.h>
#include <string.h>

#include "symboltable.h"
#include "pairMemory.h"

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
  case DOUBLE:
    printf("%f", AS_DOUBLE(value));
    break;
  case INT:
    printf("%i", AS_INT(value));
    break;
  case STR:
    printf("\"%s\"", AS_STRING(value));
    break;
  case BOOL:
    printf(AS_BOOL(value) ? "#t" : "#f");
    break;
  case SYMBOL:
    printf("%s", GET_SYMBOL_DISPLAY(value));
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
    break;
  default:
    break;
  }
}

bool isEqualValue(Value value1, Value value2) {
  bool result;
  if (value1.type != value2.type) {
    result = false;
  } else {
    ValueType valueType = value1.type;
    switch (valueType) {
    case INT:
      result = AS_INT(value1) == AS_INT(value2);
      break;
    case DOUBLE:
      result = AS_DOUBLE(value1) == AS_DOUBLE(value2);
      break;
    case STR:
      result = strcmp(AS_STRING(value1), AS_STRING(value2)) == 0;
      break;
    case BOOL:
      result = AS_BOOL(value1) == AS_BOOL(value2);
      break;
    case SYMBOL:
      result = GET_SYMBOL_INDEX(value1) == GET_SYMBOL_INDEX(value2);
      break;
    case PAIR:
      // TODO: this probably shouldn't be recursive (use a stack)
      result = isEqualValue(car(value1), car(value2))
        && isEqualValue(cdr(value1), cdr(value2));
      break;
    case NIL:
      result = true;
      break;
    default:
      result = false;
      break;
    }
  }

  return result;
}
