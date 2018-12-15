#include <stdio.h>
#include <stdlib.h>
#include "opCodes.h"

#include "interpret.h"
#include "pairMemory.h"
#include "symboltable.h"
#include "value.h"

void printBinary(int i) {
  for (int bit = 0; bit < 8; bit++)
    putchar(i & (1 << bit) ? '1' : '0');
}

int main() {
  // Initialization Steps:

  // Byte code:
  // (+ 1 2)

  /*

    CONS(1, 2) -> Pair(1, 2)
    CAR(Pair(1, 2)) -> 1
    CDR(pair(1, 2)) -> 2

    VAL_REG : { Int, 1 }
    ARGL_REG : { Pair (1, Pair (2, NULL)) }

    // Exercise VM:
    Value one = ONE;
    Value two = INT_VALUE(2);
    Value three = INT_VALUE(3);

    displayValue(one);
    printf("\n");
    displayValue(two);
    printf("\n");
    displayValue(three);
    printf("\n");
    Value pair = cons(one, cons(two, cons(three, NIL_VALUE)));
    displayValue(pair);
    printf("\n");
  */
  initMemory();
  initSymbolTable();

  //int INDEX_0 = inputSymbol(INT_VALUE(0));
  inputSymbol(INT_VALUE(1));
  inputSymbol(INT_VALUE(4));
  inputSymbol(INT_VALUE(-1));

  /*
  static Operation arr[50] = { { ASSIGN, VAL_REG, N2 },
                               { LIST, ARGL_REG, VAL_REG },
                               { ASSIGN, VAL_REG, N1 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { ASSIGN, VAL_REG, N2 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { LOAD, VAL_REG, 0x2 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { ADD, VAL_REG, ARGL_REG },
                               { EQUAL_VALUE, VAL_REG, VAL_REG, VAL_REG },
                               { TEST, NO_REGISTER, VAL_REG, 0xC },
                               { DISPLAY, NO_REGISTER, VAL_REG },
                               { DISPLAY, NO_REGISTER, VAL_REG },
                               { END }};
  */

  static Operation arr[50] = { { LOAD, ARGL_REG, 0x1 },
                               { LOAD, VAL_REG, 0x0 },
                               { LOAD, TMP_REG, 0x0 },
                               { EQUAL_VALUE, TMP_REG, ARGL_REG, TMP_REG },
                               { DISPLAY, NO_REGISTER, TMP_REG },
                               { TEST, NO_REGISTER, TMP_REG, 0x7 },
                               { GOTO, NO_REGISTER, 0xF },
                               { LIST, VAL_REG, VAL_REG },
                               { CONS, VAL_REG, ARGL_REG, VAL_REG },
                               { MULT, VAL_REG, VAL_REG },
                               { LIST, ARGL_REG, ARGL_REG },
                               { LOAD, TMP_REG, 0x2 },
                               { CONS, ARGL_REG, TMP_REG, ARGL_REG },
                               { ADD, ARGL_REG, ARGL_REG },
                               { GOTO, NO_REGISTER, 0x2 },
                               { DISPLAY, NO_REGISTER, VAL_REG },
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
