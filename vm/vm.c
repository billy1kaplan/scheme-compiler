#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"
#include "parsetree.h"

VM vm;

static void resetStack() {
  vm.stackTop = vm.stack;
}

void initVM() {
  resetStack();
}

void freeVM() {
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                             \
  do {                                                            \
    Value a = pop();                                              \
    Value b = pop();                                              \
    if (a.type == INT_TYPE && b.type == INT_TYPE) {               \
      push(INT_NODE(AS_INT(a) op AS_INT(b)));                     \
    } else if (a.type == DOUBLE_TYPE && b.type == INT_TYPE) {     \
      push(DOUBLE_NODE(AS_DOUBLE(a) op AS_INT(b)));               \
    } else if (a.type == INT_TYPE && b.type == DOUBLE_TYPE) {     \
      push(DOUBLE_NODE(AS_INT(a) op AS_DOUBLE(b)));               \
    } else if (a.type == DOUBLE_TYPE && b.type == DOUBLE_TYPE) {  \
      push(DOUBLE_NODE(AS_DOUBLE(a) op AS_DOUBLE(b)));            \
    }                                                             \
} while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_NULL: push(*makeNull()); break;
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
      case OP_ADD: BINARY_OP(+); break;
    case OP_SUBTRACT: BINARY_OP(-); break;
    case OP_MULTIPLY: BINARY_OP(*); break;
    case OP_DIVIDE: BINARY_OP(/); break;
      //case OP_NEGATE: push(-pop()); break;
    case OP_RETURN: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

//InterpretResult interpret(const char *source) {
InterpretResult interpret(Chunk *chunk, ParseNode parseNode) {
  compile(parseNode, chunk);
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  disassembleChunk(chunk, "test chunk");
  printf("Start run");
  fflush(stdout);
  run();
  printf("End run");
  fflush(stdout);
  return INTERPRET_OK;
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}
