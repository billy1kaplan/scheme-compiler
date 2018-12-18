#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "interpret.h"
#include "operations.h"
#include "pairMemory.h"
#include "symboltable.h"
#include "value.h"

Interpreter interpreter;

void initInterpreter() {}

Value *selectRegister(Dest op) {
  Value *reg;
  switch(op) {
  case NO_REGISTER:
    reg = &ZERO;
    break;
  case VAL_REG:
    reg = interpreter.valReg;
    break;
  case ARGL_REG:
    reg = interpreter.arglReg;
    break;
  case TMP_REG:
    reg = interpreter.tmpReg;
    break;
  case N0:
    reg = &ZERO;
    break;
  case N1:
    reg = &ONE;
    break;
  case N2:
    reg = &TWO;
    break;
  default:
    break;
  }
  return reg;
}

bool interpret(Operation *bytes) {
  interpreter.pc = 0;
  interpreter.valReg = &NIL_VALUE;
  interpreter.arglReg = &NIL_VALUE;
  interpreter.tmpReg = &NIL_VALUE;

  while (true) {
    Operation op = bytes[interpreter.pc];
    Value *destination = selectRegister(op.dest);
    Value *arg1 = selectRegister(op.arg1);
    Value *arg2 = selectRegister(op.arg2);

    switch(op.op) {
      case ASSIGN: {
        *destination = *arg1;
        break;
      }
      case TEST: {
        if (!IS_FALSE(*destination)) {
          interpreter.pc++;
        } else {
          interpreter.pc = op.arg1;
        }
        continue;
      }
      case EXTND: {
        Environment extendedEnv = extendEnvironment(*arg2, *arg1, interpreter.envReg);
        interpreter.envReg = &extendedEnv;
        break;
      }
      case LOOKUP:
      case CLSR:
        break;
      case GOTO:
        interpreter.pc = op.dest;
        continue;
      case LOAD:
        *destination = lookupSymbol(op.arg1);
        break;
      case CONS:
        *destination = cons(*arg1, *arg2);
        break;
      case LIST:
        *destination = cons(*arg1, NIL_VALUE);
        break;
      case ADD:
        *destination = sum(*arg1);
        break;
      case MULT:
        *destination = product(*arg1);
        break;
      case EQUAL_VALUE:
        *destination = BOOL_VALUE(isEqualValue(*arg1, *arg2));
        break;
      case DISPLAY:
        displayValue(*destination);
        break;
      case END:
        return true;
    }

    interpreter.pc++;
  }

  return true;
}
