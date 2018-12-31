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
  int depth;

} Interpreter;

void initInterpreter();

void loadConstants(LoadInstruction *loadInstructions);

bool interpret(Operation *bytes);

void push(Register value);
Register pop();

#define UPDATE_REGISTER_ENV(reg, update) (*interpreter.registers[reg].as.env = (update))
#define UPDATE_REGISTER_LINE(reg, update) (*interpreter.registers[reg].as.lineNumber = (update))
#define UPDATE_REGISTER_VAL(reg, update) (*interpreter.registers[reg].as.value = (update))

#define REGISTER_ENV(reg) (interpreter.registers[reg].as.env)
#define REGISTER_LINE(reg) (interpreter.registers[reg].as.lineNumber)
#define REGISTER_VAL(reg) (interpreter.registers[reg].as.value)

#endif
