#ifndef scheme_value_h
#define scheme_value_h

#include <stdbool.h>

typedef enum { INT, DOUBLE, STR, BOOL, SYMBOL, PAIR, NIL } ValueType;

typedef struct {
  ValueType type;
  union {
    int integerValue;
    double doubleValue;
    char *stringValue;
    bool booleanValue;
    int pairIndex;
    int symbolIndex;
  } as;
} Value;

#define IS_PAIR(value) ((value).type == PAIR)
#define IS_INT(value) ((value).type == INT)
#define IS_NULL(value) ((value).type == NIL)

#define NIL_VALUE ((Value) { NIL })
#define INT_VALUE(value) ((Value) { INT, .as.integerValue = value})
#define PAIR_VALUE(value) ((Value) { PAIR, .as.pairIndex = value})

#define AS_INT(value) ((value).as.integerValue)

typedef struct {
  int count;
  int capacity;
  Value *values;
} ValueArray;


void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);

Value vectorRef(Value *vector, int index);
void vectorSet(Value *vector, int index, Value value);

#endif
