#ifndef scheme_interpreter_h
#define scheme_interpreter_h

#include <stdbool.h>

#include "environment.h"
#include "opCodes.h"
#include "value.h"

#define MAX_STACK_DEPTH 256
#define NUM_REGISTERS 8

typedef struct {
  int pc;
  Value registers[NUM_REGISTERS];

  Value stack[MAX_STACK_DEPTH];
  Value *stackTop;
  int depth;

} Interpreter;

void initInterpreter();

void loadConstants(LoadInstruction *loadInstructions);

bool interpret(Operation *bytes);

void push(Value value);
Value pop();

#define UPDATE_REGISTER(reg, update) (interpreter.registers[reg] = (update))
#define REGISTER_VAL(reg) (interpreter.registers[reg])

#endif
