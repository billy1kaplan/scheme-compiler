#ifndef _VM_ASSEMBLER_H
#define _VM_ASSEMBLER_H

#include <stdbool.h>

typedef enum {
  OP_CONST,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_ASSIGN,
} OpCode;

typedef struct {
  int stackCount;
  int stackCapacity;
  Value *stack;

  Value *val;
  Value *argl;
} Assembler;

bool interpret();

/* Symbol lookup table */
typedef struct {
  Value *lookup(char *symbol);
} SymbolTable;
struct SymbolTable *symbols;

/* For managing memory */
typedef struct {
  int count;
  int capacity;
  Value *valueArray;
} ValueVector;

typedef struct {
  int free;
  ValueVector *the_cars;
  ValueVector *the_cdrs;
} Memory;

Value *vectorRef(ValueVector *vector, int index);
void vectorset(ValueVector *vector, int index, Value *value);

// Represents a Scheme value (Primitive)
typedef enum { INT_TYPE, DOUBLE_TYPE, STR_TYPE, BOOL_TYPE, SYMBOL_TYPE, PAIR_TYPE, NULL_TYPE } ValueType;

typedef struct {
  ValueType type;
  union {
    int integerValue;
    double doubleValue;
    char *stringValue;
    boolean booleanValue;
    int pairIndex;
    int symbolIndex;
  } as;
} Value;

Value *car(Value *pair);
Value *cdr(Value *pair);
Value *cons(Value *first, Value *second);

// Corresponding Macros
#define IS_BOOL(value) ((value).type == BOOL_TYPE)

#define BOOL_NODE(value) ((Value) { BOOL_TYPE, .as.booleanValue = value})

#define AS_BOOL(value) ((value).as.booleanValue)

#endif
