#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "environment.h"
#include "interpret.h"
#include "operations.h"
#include "pairMemory.h"
#include "symboltable.h"
#include "value.h"

Interpreter interpreter;

static void resetStack() {
  interpreter.stackTop = interpreter.stack;
  interpreter.depth = 0;
}

void initInterpreter() {
  resetStack();
}

void push(Value value) {
  printf("SAVING = ");
  displayValue(value);
  printf("\n");
  *interpreter.stackTop = value;
  printf("SAVING = ");
  displayValue(*interpreter.stackTop);
  printf("\n");
  interpreter.stackTop++;
  printf("SAVING = ");
  displayValue(*interpreter.stackTop);
  printf("\n");
}

Value pop() {
  interpreter.stackTop--;
  Value top = *interpreter.stackTop;
  printf("popping = ");
  displayValue(top);
  printf("\n");
  interpreter.depth--;
  return top;
}

void loadConstants(LoadInstruction *loadInstructions) {
  int pc = 0;
  while (true) {
    LoadInstruction currentInstruction = loadInstructions[pc];
    LoadOp op = currentInstruction.op;
    int index = currentInstruction.index;
    Value value = currentInstruction.value;

    switch(op) {
    case INPUT:
      inputConstant(index, value);
      break;
    case END_INPUT:
      return;
    }

    pc++;
  }
}

void debug(Operation op) {
  char *operation;
    switch(op.op) {
    case ASSIGN: {
      operation = "ASSIGN";
      break;
    }
    case TEST: {
      operation = "TEST";
      break;
    }
    case EXTND: {
      operation = "EXTEND_ENV";
      break;
    }
    case LOOKUP: {
      operation = "LOOKUP";
      break;
    }
    case MKPROC: {
      operation = "MKPROC";
      break;
    }
    case GOTO: {
      operation = "GOTO";
      break;
    }
    case LOAD: {
      operation = "LOAD";
      break;
    }
    case CONS: {
      operation = "CONS";
      break;
    }
    case LIST: {
      operation = "LIST";
      break;
    }
    case ADD: {
      operation = "ADD";
      break;
    }
    case EQ: {
      operation = "EQ";
      break;
    }
    case MINUS: {
      operation = "MINUS";
      break;
    }
    case MULT: {
      operation = "MULT";
      break;
    }
    case EQUAL_VALUE: {
      operation = "EQ";
      break;
    }
    case DISPLAY: {
      operation = "DISPLAY";
      break;
    }
    case SAVE: {
      operation = "SAVE";
      break;
    }
    case RESTORE: {
      operation = "RESTORE";
      break;
    }
    case ASSIGN_CONTINUE: {
      operation = "ASSIGN_CONTINUE";
      break;
    }
    case COMPILED_PROCEDURE_ENV: {
      operation = "COMPILED_PROC_ENV";
      break;
    }
    case COMPILED_PROC_ENTRY: {
      operation = "COMPILED_PROC_ENTRY";
      break;
    }
    case JUMP: {
      operation = "JUMP";
      break;
    }
    case END:
      operation = "END";
    }
    printf("EXECUTING: %s\n", operation);
}

bool interpret(Operation *bytes) {
  interpreter.pc = 0;

  interpreter.registers[ENV_REG] = BASE_ENV;
  interpreter.registers[CONTINUE_REG] = NIL_VALUE;
  interpreter.registers[PROC_REG] = NIL_VALUE;
  interpreter.registers[VAL_REG] = INT_VALUE(6);
  interpreter.registers[TMP_REG] = INT_VALUE(2);
  interpreter.registers[ARGL_REG] = NIL_VALUE;

  while (true) {
    Operation op = bytes[interpreter.pc];
    debug(op);
    printf("\nENV = ");
    displayValue(REGISTER_VAL(ENV_REG));
    printf("\n\n");
    fflush(stdout);

    switch(op.op) {
    case ASSIGN: {
      Value val = REGISTER_VAL(op.arg1);
      UPDATE_REGISTER(op.dest, val);
      break;
    }
    case TEST: {
      if (!IS_FALSE(REGISTER_VAL(op.dest))) {
        interpreter.pc++;
      } else {
        interpreter.pc = op.arg1;
      }
      continue;
    }
    case EXTND: {
      displayEnvironment(REGISTER_VAL(ENV_REG));
      Value extendedEnv = extendEnvironment(
        REGISTER_VAL(op.arg1),
        REGISTER_VAL(op.dest),
        REGISTER_VAL(ENV_REG));

      printf("wtf? ");
      displayEnvironment(extendedEnv);
      printf("\n");
      fflush(stdout);


      UPDATE_REGISTER(ENV_REG, extendedEnv);
      printf("after extnd : ");
      displayEnvironment(REGISTER_VAL(ENV_REG));

      printf("\n");
      break;
    }
    case LOOKUP: {
      printf("Looking up: ");
      displayValue(REGISTER_VAL(op.arg1));
      printf("\n");
      printf("in\n");
      displayValue(REGISTER_VAL(ENV_REG));
      printf("\n");
      fflush(stdout);
      Value lookedUpValue = lookupSymbolEnv(REGISTER_VAL(op.arg1), REGISTER_VAL(ENV_REG));
      printf("RESULT of lookup: ");
      displayValue(lookedUpValue);
      printf("\n");
      fflush(stdout);
      UPDATE_REGISTER(op.dest, lookedUpValue);
      break;
    }
    case MKPROC: {
      Value proc = MAKE_PROC(INT_VALUE(op.arg1), REGISTER_VAL(ENV_REG));
      UPDATE_REGISTER(op.dest, proc);
      break;
    }
    case GOTO: {
      interpreter.pc = op.dest;
      continue;
    }
    case LOAD: {
      Value constant = retrieveConstant(op.arg1);
      UPDATE_REGISTER(op.dest, constant);
      break;
    }
    case CONS: {
      Value consResult = cons(REGISTER_VAL(op.arg1), REGISTER_VAL(op.arg2));
      UPDATE_REGISTER(op.dest, consResult);
      break;
    }
    case LIST: {
      Value listResult = cons(REGISTER_VAL(op.arg1), NIL_VALUE);
      UPDATE_REGISTER(op.dest, listResult);
      break;
    }
    case EQ: {
      Value eqResult = nEqual(REGISTER_VAL(op.arg1));
      UPDATE_REGISTER(op.dest, eqResult);
      break;
    }
    case ADD: {
      Value sumResult = sum(REGISTER_VAL(op.arg1));
      UPDATE_REGISTER(op.dest, sumResult);
      break;
    }
    case MINUS: {
      Value minusResult = minus(REGISTER_VAL(op.arg1));
      UPDATE_REGISTER(op.dest, minusResult);
      break;
    }
    case MULT: {
      Value productResult = product(REGISTER_VAL(op.arg1));
      UPDATE_REGISTER(op.dest, productResult);
      break;
    }
    case EQUAL_VALUE: {
      Value equalityCheck = BOOL_VALUE(isEqualValue(
        REGISTER_VAL(op.arg1),
        REGISTER_VAL(op.arg2)));
      UPDATE_REGISTER(op.dest, equalityCheck);
      break;
    }
    case DISPLAY: {
      printf("DISPLAYING = ");
      displayValue(REGISTER_VAL(op.dest));
      printf("\n");
      break;
    }
    case SAVE: {
      push(REGISTER_VAL(op.dest));
      break;
    }
    case RESTORE: {
      UPDATE_REGISTER(op.dest, pop());
      break;
    }
    case ASSIGN_CONTINUE: {
      Value line = INT_VALUE(op.dest);
      UPDATE_REGISTER(CONTINUE_REG, line);
      break;
    }
    case COMPILED_PROC_ENTRY: {
      Value lineNumber = GET_PROC_LABEL(REGISTER_VAL(op.arg1));
      UPDATE_REGISTER(op.dest, lineNumber);
      break;
    }
    case COMPILED_PROCEDURE_ENV: {
      Value env = GET_PROC_ENV(REGISTER_VAL(op.arg1));
      UPDATE_REGISTER(op.dest, env);
      break;
    }
    case JUMP:
      printf("JUMP VAL = ");
      fflush(stdout);
      displayValue(REGISTER_VAL(op.dest));
      printf("\n");
      fflush(stdout);
      interpreter.pc = AS_INT(REGISTER_VAL(op.dest));
      continue;
    case END:
      return true;
    };

    interpreter.pc++;
  }

  return true;
}
