#ifndef scheme_value_h
#define scheme_value_h

#include <stdbool.h>

typedef enum { INT, DOUBLE, STR, BOOL, SYMBOL, PAIR, CLOSURE, NIL } ValueType;

// Forward declaration
struct closure;

typedef struct {
  ValueType type;
  union {
    int integerValue;
    double doubleValue;
    char *stringValue;
    bool booleanValue;
    int pairIndex;
    int symbolIndex;
    struct closure *closure;
  } as;
} Value;

#define IS_PAIR(value) ((value).type == PAIR)
#define IS_DOUBLE(value) ((value).type == DOUBLE)
#define IS_INT(value) ((value).type == INT)
#define IS_BOOL(value) ((value).type == BOOL)
#define IS_NULL(value) ((value).type == NIL)

#define INT_VALUE(value) ((Value) { INT, .as.integerValue = value})
#define DOUBLE_VALUE(value) ((Value) { DOUBLE, .as.doubleValue = value})
#define STRING_VALUE(value) ((Value) { STR, .as.stringValue = value})
#define BOOL_VALUE(value) ((Value) { BOOL, .as.booleanValue = value})
#define PAIR_VALUE(value) ((Value) { PAIR, .as.pairIndex = value})
#define NIL_VALUE ((Value) { NIL })

#define AS_INT(value) ((value).as.integerValue)
#define AS_DOUBLE(value) ((value).as.doubleValue)
#define AS_STRING(value) ((value).as.stringValue)
#define AS_BOOL(value) ((value).as.booleanValue)

#define GET_SYMBOL_INDEX(value) ((value).as.symbolIndex)

#define CAST_INT_TO_DOUBLE(value) (DOUBLE_VALUE((double)AS_INT(value)))

#define IS_FALSE(value) (IS_BOOL(value) && !AS_BOOL(value))

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
