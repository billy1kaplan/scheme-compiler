#include <stdio.h>
#include <string.h>

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

static void emitOperation(Chunk *chunk, ParseNode parseNode) {
  switch (parseNode.s[0]) {
  case '+':
    emitByte(chunk, OP_ADD);
    break;
  case '-':
    emitByte(chunk, OP_SUBTRACT);
    break;
  case '*':
    emitByte(chunk, OP_MULTIPLY);
    break;
  default:
    //Lookup symbol operation
    break;
  }
}

static bool streq(const ParseNode *node, const char *str) {
  return strcmp(node->s, str) == 0;
}

static bool compileInternal(Chunk *chunk, ParseNode parseNode) {
  switch(parseNode.type) {
  case NULL_TYPE: emitNull(chunk); break;
  case STR_TYPE: emitConstant(chunk, parseNode); break;
  case INT_TYPE: emitConstant(chunk, parseNode); break;
  case DOUBLE_TYPE: emitConstant(chunk, parseNode); break;
  case SYMBOL_TYPE: emitOperation(chunk, parseNode); break;
  case PAIR_TYPE: {
    if (IS_SYMBOL(*car(&parseNode)) && streq(car(&parseNode), "lambda")) {
    } else {
      return (compileOperands(chunk, *cdr(&parseNode)) &&
              compileInternal(chunk, *car(&parseNode)));
    }
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
