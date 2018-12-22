#include <stdio.h>

#include "pairMemory.h"
#include "environment.h"

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

// TODO: Eventually this should be an error
void testFailedLookup() {
  Value expected = NIL_VALUE;
  Value symbol = INT_VALUE(1);
  Value actual = lookupSymbolEnv(symbol, BASE_ENV);
  testValueEquality("Symbol does not exist in the environment", expected, actual);
}

void testExtendAndSuccessfulLookup() {
  Value variable = INT_VALUE(1);
  Value value = STRING_VALUE("Hello world!");

  Value expected = value;
  Value actual = lookupSymbolEnv(variable, extendEnvironment(LIST(value), LIST(variable), &BASE_ENV));
  testValueEquality("Symbol does exist with the proper value", expected, actual);
}

void testFailedLookupInExtended() {
  Value expected = NIL_VALUE;
  Value symbol = INT_VALUE(1);
  Value actual = lookupSymbolEnv(INT_VALUE(2), BASE_ENV);
  testValueEquality("Symbol does not exist in the environment", expected, actual);
}


int main() {
  testFailedLookup();
  testFailedLookupInExtended();
  testExtendAndSuccessfulLookup();
}
