#include <stdio.h>

#include "pairMemory.h"
#include "symboltable.h"

void testInt(char *msg, int expected, int actual) {
  if (actual == expected) {
    printf(".");
  } else {
    printf("X\n\nTest Failed: %s. Expected: %i Actual: %i\n\n", msg, expected, actual);
  }
}

void testValueEquality(char *msg, Value expected, Value actual) {
  if (isEqualValue(expected, actual)) {
    printf(".");
  } else {
    printf("X\n\nFailed: %s. Expected: ", msg);
    displayValue(expected);
    printf(" Actual: ");
    displayValue(actual);
    printf("\n\n");
  }
}

void testInputSymbol() {
  Value symbol = INT_VALUE(5);
  int index = inputSymbol(symbol);
  testValueEquality("Retrieve symbol", symbol, lookupSymbol(index));
}

void testMultipleInputSymbols() {
  Value symbol1 = INT_VALUE(1);
  int index1 = inputSymbol(symbol1);
  Value symbol2 = INT_VALUE(2);
  int index2 = inputSymbol(symbol2);
  Value symbol3 = INT_VALUE(3);
  int index3 = inputSymbol(symbol3);

  testValueEquality("Retrieve symbol 1", symbol1, lookupSymbol(index1));
  testValueEquality("Retrieve symbol 2", symbol2, lookupSymbol(index2));
  testValueEquality("Retrieve symbol 3", symbol3, lookupSymbol(index3));
}

void testMultipleInputSymbolsWithCollisions() {
  Value symbol1 = INT_VALUE(1);
  int index1 = inputSymbol(symbol1);
  Value symbol2 = INT_VALUE(2);
  int index2 = inputSymbol(symbol2);
  Value symbol3 = INT_VALUE(1);
  int index3 = inputSymbol(symbol3);

  testInt("Same symbol location", index1, index3);
}

void testComplexTable() {
  Value symbol1 = STRING_VALUE("This is a string.");
  int index1 = inputSymbol(symbol1);
  Value symbol2 = INT_VALUE(2);
  int index2 = inputSymbol(symbol2);
  Value symbol3 = INT_VALUE(1);
  int index3 = inputSymbol(symbol3);
  Value symbol4 = INT_VALUE(2);
  int index4 = inputSymbol(symbol4);
  Value symbol5 = INT_VALUE(2);
  int index5 = inputSymbol(symbol5);

  testInt("Symbol location for two is consistent", index2, index4);
  testInt("Symbol location for two is consistent", index4, index5);

  testValueEquality("Retrieve symbol 1", symbol1, lookupSymbol(index1));
  testValueEquality("Retrieve symbol 2", symbol2, lookupSymbol(index2));
  testValueEquality("Retrieve symbol 3", symbol3, lookupSymbol(index3));
  testValueEquality("Retrieve symbol 4", symbol4, lookupSymbol(index4));
  testValueEquality("Retrieve symbol 5", symbol5, lookupSymbol(index5));
}

void beforeAll() {
  initSymbolTable();
}

int main() {
  beforeAll();
  testInputSymbol();

  beforeAll();
  testMultipleInputSymbols();

  beforeAll();
  testMultipleInputSymbolsWithCollisions();

  beforeAll();
  testComplexTable();
}
