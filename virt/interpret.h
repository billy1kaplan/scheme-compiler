#ifndef scheme_interpreter_h
#define scheme_interpreter_h

#include <stdbool.h>

#include "environment.h"
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

  Environment *envReg;

  // Registers
  // Stack <-- !!!

} Interpreter;

void initInterpreter();
bool interpret(Operation *bytes);

#endif
