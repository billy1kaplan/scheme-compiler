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

  inputSymbol(INT_VALUE(3));
  inputSymbol(INT_VALUE(2));
  inputSymbol(INT_VALUE(1));

  /*
    VAL_REG = 0
    ARGL_REG = (0, NIL)
   */

  static Operation arr[50] = { { LOAD, VAL_REG, 0 },
                               { LIST, ARGL_REG, VAL_REG },
                               { LOAD, VAL_REG, 1 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { LOAD, VAL_REG, 2 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { ADD, VAL_REG, ARGL_REG,  },
                               { DISPLAY, VAL_REG },
                               { END } };

  /*
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

  printf("%i", inputSymbol(STRING_VALUE("n")));
  printf("%i", inputSymbol(LIST(STRING_VALUE("n"))));


  static Operation arr[50] =  {
                               { MKPROC, TMP_REG, 3 },
                               { ASSIGN, PROC_REG, TMP_REG },
                               { GOTO, 14 },
                               { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG },
                               { EXTND, 1, ARGL_REG },
                               { LOAD, VAL_REG, 1 },
                               { LIST, TMP_REG, VAL_REG },
                               { ASSIGN, ARGL_REG, TMP_REG },
                               { LOOKUP, VAL_REG, 0, },
                               { CONS, TMP_REG, VAL_REG, ARGL_REG },
                               { ASSIGN, ARGL_REG, TMP_REG },
                               { ADD, TMP_REG, ARGL_REG, },
                               { ASSIGN, VAL_REG, TMP_REG, },
                               { JUMP, CONT_REG, },
                               { LOAD, VAL_REG, 1 },
                               { LIST, TMP_REG, VAL_REG, },
                               { ASSIGN, ARGL_REG, TMP_REG },
                               { ASSIGN_CONTINUE, 19 },
                               { JUMP, PROC_REG },
  };
  */

/*
  static Operation arr[50] = { { LOAD, ARGL_REG, 0x0},
  { LIST, ARGL_REG, ARGL_REG },
  { LOAD, VAL_REG, 0x1 },
  { LIST, VAL_REG, VAL_REG },
  { EXTND, ARGL_REG, VAL_REG },
  { LOAD, ARGL_REG, 0x0 },
  { LOOKUP, TMP_REG, ARGL_REG },
  { DISPLAY, TMP_REG },
  { END } };

*/

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
