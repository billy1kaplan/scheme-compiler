#ifndef scheme_interpreter_h
#define scheme_interpreter_h

#include <stdbool.h>

#include "environment.h"
#include "opCodes.h"
#include "value.h"

#define MAX_STACK_DEPTH 256
#define NUM_REGISTERS 8

typedef struct {
  union {
    Value *value;
    Environment *env;
    int *lineNumber;
  } as;
} Register;

typedef struct {
  int pc;
  Register registers[NUM_REGISTERS];

  Register stack[MAX_STACK_DEPTH];
  Register *stackTop;

} Interpreter;

void initInterpreter();
bool interpret(Operation *bytes);

void push(Register *value);
Register pop();

#endif
