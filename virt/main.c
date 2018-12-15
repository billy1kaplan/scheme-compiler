#include <stdio.h>
#include "opCodes.h"

#include "interpret.h"
#include "pairMemory.h"
#include "value.h"

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

  static Operation arr[50] = { { ASSIGN, VAL_REG, N2 },
                               { LIST, ARGL_REG, VAL_REG },
                               { ASSIGN, VAL_REG, N1 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { ASSIGN, VAL_REG, N2 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { ASSIGN, VAL_REG, N2 },
                               { CONS, ARGL_REG, VAL_REG, ARGL_REG },
                               { MULT, VAL_REG, ARGL_REG },
                               { DISPLAY, NO_REGISTER, VAL_REG },
                               { END }};

  interpret(arr);
  printf("\nDONE\n");
}
