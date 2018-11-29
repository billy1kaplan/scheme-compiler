#ifndef scheme_chunk_h
#define scheme_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  CONTINUE,
  RETURN
} Register;

typedef enum {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN,
  OP_NULL,
  OP_GOTO,
  OP_ASSIGN,
  OP_MOV,
  OP_CONS,
  OP_LIST,
} OpCode;

struct LineNumber {
  uint8_t count;
  int lineNumber;
};

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int lineCount;
  int lineCapacity;
  struct LineNumber *lines;
  ValueArray constants;
} Chunk;

/* Initialize an empty chunk */
void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);
int getLine(Chunk *chunk, int index);

#endif
