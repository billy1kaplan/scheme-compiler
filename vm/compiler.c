#include <stdio.h>

#include "compiler.h"
#include "parsetree.h"

static void emitByte(Chunk *chunk, uint8_t byte) {
  writeChunk(chunk, byte, 1);
}

static void emitBytes(Chunk *chunk, uint8_t byte1, uint8_t byte2) {
  writeChunk(chunk, byte1, 1);
  writeChunk(chunk, byte2, 1);
}

static void emitReturn(Chunk *chunk) {
  emitByte(chunk, OP_RETURN);
}

static uint8_t makeConstant(Chunk *chunk, Value value) {
  int constant = addConstant(chunk, value);
  if (constant > UINT8_MAX) {
    // ERR
    return 0;
  }

  return (uint8_t)constant;
}

static void emitConstant(Chunk *chunk, Value value) {
  emitBytes(chunk, OP_CONSTANT, makeConstant(chunk, value));
}

static void emitNull(Chunk *chunk) {
  emitByte(chunk, OP_NULL);
}

static bool compileInternal(Chunk *chunk, ParseNode parseNode);

static bool compileOperands(Chunk *chunk, ParseNode parseNode) {
  bool status = true;
  ParseNode *current = reverseOne(&parseNode);
  emitNull(chunk);
  while (current->type != NULL_TYPE) {
    status = status && compileInternal(chunk, *current->consCell.car);
    current = current->consCell.cdr;
  }

  return status;
}

static bool compileInternal(Chunk *chunk, ParseNode parseNode) {
  switch(parseNode.type) {
  case NULL_TYPE: emitNull(chunk); break;
  case INT_TYPE: emitConstant(chunk, parseNode); break;
  case DOUBLE_TYPE: emitConstant(chunk, parseNode); break;
  case SYMBOL_TYPE: emitByte(chunk, OP_ADD); break;
  case PAIR_TYPE: {
    return (compileOperands(chunk, *parseNode.consCell.cdr) &&
            compileInternal(chunk, *parseNode.consCell.car));
  }
  default:
    break;
  }

  return true;
}

// TODO: get proper line number from the parser
bool compile(ParseNode parseNode, Chunk *chunk) {
  bool status = compileInternal(chunk, parseNode);
    if (status) {
      emitReturn(chunk);
    }
    return status;
}
