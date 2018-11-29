#ifndef scheme_vm_h
#define scheme_vm_h

#include "chunk.h"

#define STACK_MAX 256

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value stack[STACK_MAX];
  Value *stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
//InterpretResult interpret(const char *source);
InterpretResult interpret(Chunk *chunk, ParseNode parseNode);
void push(Value value);
Value pop();

#endif
