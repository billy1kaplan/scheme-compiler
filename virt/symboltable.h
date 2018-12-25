#ifndef _scheme_symboltable_h
#define _scheme_symboltable_h

#include "value.h"

#define MAX_CONSTANTS 8192

typedef struct {
  char *symbols[MAX_CONSTANTS];
  int size;
} SymbolTable;

void initSymbolTable();

// Places a symbol into the symbol table and returns the index of placement
int inputSymbol(char *symbol);

#define SYMBOL_VALUE(value) ((Value) { SYMBOL, .as.symbol = &((SymbolEntry) { inputSymbol(value), value }) })

#define GET_SYMBOL_INDEX(value) ((value).as.symbol->index)
#define GET_SYMBOL_DISPLAY(value) ((value).as.symbol->displayString)


#endif
