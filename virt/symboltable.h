#ifndef _scheme_symboltable_h
#define _scheme_symboltable_h

#include "value.h"

#define MAX_CONSTANTS 8192

typedef struct {
  Value symbols[MAX_CONSTANTS];
  int size;
} SymbolTable;

void initSymbolTable();

// Places a symbol into the symbol table and returns the index of placement
int inputSymbol(Value symbol);

// Returns the symbol at a given lookup location
Value lookupSymbol(int index);

#endif
