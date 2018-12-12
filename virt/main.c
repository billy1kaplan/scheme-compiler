#include <stdio.h>
#include "opCodes.h"

#include "interpret.h"
#include "pairMemory.h"
#include "value.h"

int main() {
  // Initialization Steps:
  initMemory();

  // Byte code:
  static Operation arr[50] = { { LOAD, VAL, N2, NO_REGISTER },
                               { LIST, ARGL, VAL, NO_REGISTER }};
  /*

  static OpCode arr[50] = { FROM_VAL,
                            N_2,
                            FROM_ARGL,
                            LIST_VAL,
                            ASSIGN_ARGL,
                            DISPLAY };
                            N_1,
                            ASSIGN_ARGL,
                            CONS,
                            REG_VAL,
                            REG_ARGL,
                            OP_ADD,
                            REG_ARGL,
                            DISPLAY }; */

  // Exercise VM:
  Value one = INT_VALUE(1);
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

  interpret(11, arr);
  printf("\nDONE\n");
}
