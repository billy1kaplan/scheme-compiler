#include <stdio.h>
#include <stdlib.h>
#include "opCodes.h"

#include "interpret.h"
#include "constants.h"
#include "pairMemory.h"
#include "symboltable.h"
#include "value.h"

void printBinary(int i) {
  for (int bit = 0; bit < 8; bit++)
    putchar(i & (1 << bit) ? '1' : '0');
}

int main() {
  initMemory();
  initSymbolTable();

  inputSymbol(INT_VALUE(1));
  inputSymbol(INT_VALUE(4));
  inputSymbol(INT_VALUE(-1));

  static Operation arr[50] = { { LOAD, ARGL_REG, 0x1 },
                               { LOAD, VAL_REG, 0x0 },
                               { ASSIGN, TMP_REG, N1 },
                               { EQUAL_VALUE, TMP_REG, ARGL_REG, TMP_REG },
                               { TEST, TMP_REG, 0x6 },
                               { GOTO,  0xE },
                               { LIST, VAL_REG, VAL_REG },
                               { CONS, VAL_REG, ARGL_REG, VAL_REG },
                               { MULT, VAL_REG, VAL_REG },
                               { LIST, ARGL_REG, ARGL_REG },
                               { LOAD, TMP_REG, 0x2 },
                               { CONS, ARGL_REG, TMP_REG, ARGL_REG },
                               { ADD, ARGL_REG, ARGL_REG },
                               { GOTO,  0x2 },
                               { DISPLAY, VAL_REG },
                               { END } };
  int i = 0;
  while (i == 0 || arr[i - 1].op != END) {
    Operation op = arr[i];
    printBinary(op.op);
    printBinary(op.dest);
    printBinary(op.arg1);
    printBinary(op.arg2);
    putchar('\n');
    i++;
  }

  interpret(arr);
  printf("\nDONE\n");
}
