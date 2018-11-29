#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lineCount = 0;
  chunk->lineCapacity = 0;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(struct LineNumber, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(chunk->code, uint8_t,
                             oldCapacity, chunk->capacity);
  }

  if (chunk->lineCapacity < chunk->lineCount + 1) {
    int oldCapacity = chunk->lineCapacity;
    chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
    chunk->lines = GROW_ARRAY(chunk->lines, struct LineNumber,
                              oldCapacity, chunk->lineCapacity);
  }

  if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount - 1].lineNumber == line ) {
    chunk->lines[chunk->lineCount - 1].count++;
  } else {
    chunk->lines[chunk->lineCount].lineNumber = line;
    chunk->lines[chunk->lineCount].count = 1;
    chunk->lineCount++;
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int index) {
  int lineIndex = 0;
  int count = chunk->lines[lineIndex].count;

  while (count <= index) {
    lineIndex++;
    count += chunk->lines[lineIndex].count;
  }

  return chunk->lines[lineIndex].lineNumber;
}
