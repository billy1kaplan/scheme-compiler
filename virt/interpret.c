#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "interpret.h"
#include "pairMemory.h"

Interpreter interpreter;

void initInterpreter() {}

bool interpret(int length, Operation *bytes) {
  interpreter.pc = 0;
  interpreter.valReg = &NIL_VALUE;
  interpreter.arglReg = &NIL_VALUE;
  interpreter.tmpReg = &NIL_VALUE;
  interpreter.selectedReg = interpreter.valReg;

  while (interpreter.pc < length) {
    Operation op = bytes[interpreter.pc];

    switch(op.op) {
    case N0:
      *interpreter.selectedReg = ZERO;
      break;
    case N_1:
      *interpreter.selectedReg = ONE;
      break;
    case N_2:
      *interpreter.selectedReg = TWO;
      break;
    case ASSIGN_VAL:
      interpreter.valReg = interpreter.tmpReg;
      break;
    case ASSIGN_ARGL:
      interpreter.arglReg = interpreter.tmpReg;
      break;
    case FROM_VAL:
      interpreter.selectedReg = interpreter.valReg;
      break;
    case FROM_ARGL:
      interpreter.selectedReg = interpreter.arglReg;
      break;
    case CONS:
      break;
    case LIST_VAL: {
      Value val = cons(*interpreter.selectedReg, NIL_VALUE);
      *interpreter.tmpReg = val;
      break;
    }
    case OP_ADD: {
      interpreter.pc++;

      Value result = ZERO;
      Value args = *interpreter.valReg;
      while (!IS_NULL(args)) {
        result.as.integerValue += AS_INT(car(args));
        args = cdr(args);
      }

      interpreter.valReg = &result;
      break;
    }
    case DISPLAY:
      displayValue(*interpreter.valReg);
      break;
    }

    interpreter.pc++;
  }

  return true;
}
