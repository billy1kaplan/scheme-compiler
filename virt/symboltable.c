#include <string.h>

#include "pairMemory.h"
#include "symboltable.h"

SymbolTable symbolTable;

void initSymbolTable() {
  symbolTable.size = 0;
}

int inputSymbol(char *symbol) {
  int index = -1;
  for (int i = 0; i < symbolTable.size; i++) {
    if (strcmp(symbol, symbolTable.symbols[i]) == 0) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    symbolTable.symbols[symbolTable.size] = symbol;
    index = symbolTable.size;
    symbolTable.size++;
  }
  return index;
}
