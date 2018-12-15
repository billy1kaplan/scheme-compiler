#include "pairMemory.h"
#include "symboltable.h"

SymbolTable symbolTable;

void initSymbolTable() {
  symbolTable.size = 0;
}

int inputSymbol(Value symbol) {
  int index = -1;
  for (int i = 0; i < symbolTable.size; i++) {
    if (isEqualValue(symbol, symbolTable.symbols[i])) {
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

Value lookupSymbol(int index) {
  return symbolTable.symbols[index];
}
