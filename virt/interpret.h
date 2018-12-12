#ifndef scheme_interpreter_h
#define scheme_interpreter_h

#include <stdbool.h>

#include "opCodes.h"
#include "value.h"

typedef struct {
  Value value;
} Register;

typedef struct {
  int pc;
  Value *valReg;
  Value *arglReg;
  Value *tmpReg;
  Value *selectedReg;
  // Registers
  // Stack

} Interpreter;

void initInterpreter();
bool interpret(int length, Operation *bytes);

#endif
