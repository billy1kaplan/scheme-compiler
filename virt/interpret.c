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

void push(Register regValue) {
  *interpreter.stackTop = regValue;
  interpreter.stackTop++;
}

Register pop() {
  Register top = *interpreter.stackTop;
  interpreter.stackTop--;
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
    case LAMBDA_OP:
      operation = "LAMBDA";
      break;
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
}

bool interpret(Operation *bytes) {
  interpreter.pc = 0;

  interpreter.registers[ENV_REG].as.env = &BASE_ENV;

  interpreter.registers[CONTINUE_REG].as.value = &NIL_VALUE;
  interpreter.registers[PROC_REG].as.value = &NIL_VALUE;
  interpreter.registers[VAL_REG].as.value = &INT_VALUE(6);
  interpreter.registers[TMP_REG].as.value = &INT_VALUE(2);
  interpreter.registers[ARGL_REG].as.value = &NIL_VALUE;

  while (true) {
    Operation op = bytes[interpreter.pc];
    debug(op);
    fflush(stdout);

    switch(op.op) {
    case ASSIGN: {
      Value val = *REGISTER_VAL(op.arg1);
      UPDATE_REGISTER_VAL(op.dest, val);
      break;
    }
    case TEST: {
      if (!IS_FALSE(*REGISTER_VAL(op.dest))) {
        interpreter.pc++;
      } else {
        interpreter.pc = op.arg1;
      }
      continue;
    }
    case LAMBDA_OP: {
      Value lambda = LAMBDA_VALUE(
        *REGISTER_VAL(op.arg1),
        *REGISTER_VAL(op.arg2));

      UPDATE_REGISTER_VAL(op.dest, lambda);
      break;
    }
    case EXTND: {
      displayEnvironment(*REGISTER_ENV(ENV_REG));
      Environment extendedEnv = extendEnvironment(
        *REGISTER_VAL(op.arg1),
        *REGISTER_VAL(op.dest),
        *REGISTER_ENV(ENV_REG));

      printf("wtf? ");
      displayEnvironment(extendedEnv);
      printf("\n");
      fflush(stdout);


      UPDATE_REGISTER_ENV(ENV_REG, extendedEnv);
      printf("after extnd : ");
      displayEnvironment(*REGISTER_ENV(ENV_REG));

      printf("\n");
      break;
    }
    case LOOKUP: {
      printf("Here?");
      printf("\n");
      fflush(stdout);
      printf("\nLooking up: ");
      fflush(stdout);
      displayValue(*REGISTER_VAL(op.arg1));
      printf("\n");
      fflush(stdout);
      printf("PROC REG : ");
      displayValue(*REGISTER_VAL(PROC_REG));
      printf("\n");
      Value lookedUpValue = lookupSymbolEnv(*REGISTER_VAL(op.arg1),
        *REGISTER_ENV(ENV_REG));
      UPDATE_REGISTER_VAL(op.dest, lookedUpValue);
      printf("\nRES IS: ");
      fflush(stdout);
      displayValue(*REGISTER_VAL(op.dest));
      printf("\n");
      fflush(stdout);
      printf("PROC REG : ");
      displayValue(*REGISTER_VAL(PROC_REG));
      printf("\n");
      break;
    }
    case MKPROC: {
      Value proc = MAKE_PROC(op.arg1, *REGISTER_ENV(ENV_REG));
      printf("%i", op.dest);
      //*destination->as.value = proc;
      UPDATE_REGISTER_VAL(op.dest, proc);
      displayValue(*interpreter.registers[PROC_REG].as.value);
      printf("d\n");
      printf("%i\n", GET_PROC_LABEL(*interpreter.registers[PROC_REG].as.value));
      printf("%p, %p\n", REGISTER_VAL(PROC_REG), REGISTER_LINE(VAL_REG));
      break;
    }
    case GOTO: {
      interpreter.pc = op.dest;
      continue;
    }
    case LOAD: {
      Value constant = retrieveConstant(op.arg1);
      printf("LOAD %i\n", op.arg1);
      fflush(stdout);
      UPDATE_REGISTER_VAL(op.dest, constant);
      //*destination->as.value = constant;
      break;
    }
    case CONS: {
      Value consResult = cons(*REGISTER_VAL(op.arg1), *REGISTER_VAL(op.arg2));
      UPDATE_REGISTER_VAL(op.dest, consResult);
      break;
    }
    case LIST: {
      Value listResult = cons(*REGISTER_VAL(op.arg1), NIL_VALUE);
      UPDATE_REGISTER_VAL(op.dest, listResult);
      break;
    }
    case EQ: {
      Value eqResult = nEqual(*REGISTER_VAL(op.arg1));
      UPDATE_REGISTER_VAL(op.dest, eqResult);
      break;
    }
    case ADD: {
      Value sumResult = sum(*REGISTER_VAL(op.arg1));
      UPDATE_REGISTER_VAL(op.dest, sumResult);
      break;
    }
    case MINUS: {
      Value minusResult = minus(*REGISTER_VAL(op.arg1));
      UPDATE_REGISTER_VAL(op.dest, minusResult);
      break;
    }
    case MULT: {
      Value productResult = product(*REGISTER_VAL(op.arg1));
      UPDATE_REGISTER_VAL(op.dest, productResult);
      break;
    }
    case EQUAL_VALUE: {
      Value equalityCheck = BOOL_VALUE(isEqualValue(
        *REGISTER_VAL(op.arg1),
        *REGISTER_VAL(op.arg2)));
      UPDATE_REGISTER_VAL(op.dest, equalityCheck);
      break;
    }
    case DISPLAY: {
      printf("DISPLAYING = ");
      displayValue(*REGISTER_VAL(op.dest));
      printf("\n");
      break;
    }
    case SAVE: {
      push(interpreter.registers[op.dest]);
      break;
    }
    case RESTORE: {
      Register top = pop();
      *interpreter.registers[op.dest].as.env  = *top.as.env;
      break;
    }
    case ASSIGN_CONTINUE: {
      int ln = op.dest;
      UPDATE_REGISTER_LINE(CONTINUE_REG, ln);
      printf("assigned to %i\n", *REGISTER_LINE(CONTINUE_REG));
      break;
    }
    case COMPILED_PROC_ENTRY: {
      fflush(stdout);
      printf("%p, %p\n", REGISTER_VAL(op.arg1), REGISTER_VAL(op.dest));
      displayValue(*REGISTER_VAL(op.arg1));
      printf("\n");
      fflush(stdout);
      int lineNumber = GET_PROC_LABEL(*REGISTER_VAL(op.arg1));
      printf("before to %i\n", lineNumber);
      fflush(stdout);
      UPDATE_REGISTER_LINE(op.dest, lineNumber);
      printf("%p, %p\n", REGISTER_VAL(op.arg1), REGISTER_LINE(op.dest));
      printf("%p, %p\n", REGISTER_VAL(PROC_REG), REGISTER_LINE(VAL_REG));
      break;
    }
    case COMPILED_PROCEDURE_ENV: {
      Environment env = GET_PROC_ENV(*REGISTER_VAL(op.arg1));
      UPDATE_REGISTER_ENV(op.dest, env);
      break;
    }
    case JUMP:
      interpreter.pc = *REGISTER_LINE(op.dest);
      printf(" TO %i\n", interpreter.pc);
      continue;
    case END:
      return true;
    };

    interpreter.pc++;
  }

  return true;
}
