#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "interpret.h"
#include "operations.h"
#include "pairMemory.h"
#include "symboltable.h"
#include "value.h"

Interpreter interpreter;

static void resetStack() {
  interpreter.stackTop = interpreter.stack;
}

void initInterpreter() {
  resetStack();
}

void push(Register *value) {
  *interpreter.stackTop = *value;
  interpreter.stackTop++;
}

Register pop() {
  Register top = *interpreter.stackTop;
  interpreter.stackTop--;
  return top;
}

void pushLine(int value) {
  Register top = *interpreter.stackTop;
  top.as.lineNumber = &value;
  interpreter.stackTop++;
}

int popLine() {
  Register top = *interpreter.stackTop;
  interpreter.stackTop--;
  return *top.as.lineNumber;
}

Register *selectRegister(Dest op) {
  Register *reg;
  switch(op) {
  case VAL_REG:
  case ARGL_REG:
  case TMP_REG:
  case CONT_REG:
  case PROC_REG:
  case ENV_REG:
    reg = &interpreter.registers[op];
    break;
  default:
    break;
  }
  return reg;
}

bool interpret(Operation *bytes) {
  interpreter.pc = 0;

  while (true) {
    Operation op = bytes[interpreter.pc];
    Register *destination = selectRegister(op.dest);
    Register *arg1 = selectRegister(op.arg1);
    Register *arg2 = selectRegister(op.arg2);

    switch(op.op) {
    case ASSIGN: {
      *destination = *arg1;
      break;
    }
    case TEST: {
      if (!IS_FALSE(*destination->as.value)) {
        interpreter.pc++;
      } else {
        interpreter.pc = op.arg1;
      }
      continue;
    }
    case LAMBDA_OP:
      destination->as.value = &LAMBDA_VALUE(*arg1->as.value, *arg2->as.value);
      break;
    case EXTND: {
      Environment extendedEnv = extendEnvironment(*arg1->as.value, *destination->as.value, selectRegister(ENV_REG)->as.env);
      Register envReg = *selectRegister(ENV_REG);
      envReg.as.env = &extendedEnv;
      break;
    }
    case LOOKUP: {
      Value lookedUpValue = lookupSymbolEnv(*arg1->as.value, *selectRegister(ENV_REG)->as.env);

      destination->as.value = &lookedUpValue;
      break;
    }
    case MKPROC: {
      destination->as.value = &MAKE_PROC(op.dest, *selectRegister(ENV_REG)->as.env);
      break;
    }
    case GOTO: {
      interpreter.pc = op.dest;
      continue;
    }
    case LOAD: {
      Value constant = lookupSymbol(op.arg1);
      destination->as.value = &constant;
      break;
    }
    case CONS: {
      Value consResult = cons(*arg1->as.value, *arg2->as.value);
      destination->as.value = &consResult;
      break;
    }
    case LIST: {
      Value listResult = cons(*arg1->as.value, NIL_VALUE);
      destination->as.value = &listResult;
      break;
    }
    case ADD: {
      Value sumResult = sum(*arg1->as.value);
      destination->as.value = &sumResult;
      break;
    }
    case MULT: {
      Value productResult = product(*arg1->as.value);
      destination->as.value = &productResult;
      break;
    }
    case EQUAL_VALUE: {
      Value equalityCheck = BOOL_VALUE(isEqualValue(*arg1->as.value, *arg2->as.value));
      destination->as.value = &equalityCheck;
      break;
    }
    case DISPLAY: {
      displayValue(*destination->as.value);
      break;
    }
    case SAVE: {
      push(destination);
      break;
    }
    case RESTORE: {
      *destination = pop();
      break;
    }
    case ASSIGN_CONTINUE: {
      Register continueReg = *selectRegister(CONT_REG);
      continueReg.as.lineNumber = (int *)&op.dest;
      break;
    }
    case COMPILED_PROCEDURE_ENV: {
      Environment env = GET_PROC_ENV(*arg1->as.value);
      destination->as.env = &env;
    }
    case JUMP:
    case END:
      return true;
    }

    interpreter.pc++;
  }

  return true;
}
