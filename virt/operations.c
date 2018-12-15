#include "operations.h"
#include "constants.h"
#include "pairMemory.h"

#include <stdio.h>

Value product(Value args) {
  Value head = args;
  Value result = ONE;
  while (!IS_NULL(head)) {
    if (IS_INT(result) && IS_DOUBLE(car(head))) {
      result = CAST_INT_TO_DOUBLE(result);
    }

    if (IS_DOUBLE(result) && IS_DOUBLE(car(head))) {
      result = DOUBLE_VALUE(AS_DOUBLE(result)
                            * AS_DOUBLE(car(head)));
    } else if (IS_DOUBLE(result) && IS_INT(car(head))) {
      result = DOUBLE_VALUE(AS_DOUBLE(result)
                            * AS_DOUBLE(CAST_INT_TO_DOUBLE(car(head))));
    } else {
      result = INT_VALUE(AS_INT(result) * AS_INT(car(head)));
    }

    head = cdr(head);
  }

  return result;
}

Value sum(Value args) {
  Value head = args;
  Value result = ZERO;
  while (!IS_NULL(head)) {
    if (IS_INT(result) && IS_DOUBLE(car(head))) {
      result = CAST_INT_TO_DOUBLE(result);
    }

    if (IS_DOUBLE(result) && IS_DOUBLE(car(head))) {
      result = DOUBLE_VALUE(AS_DOUBLE(result)
                            + AS_DOUBLE(car(head)));
    } else if (IS_DOUBLE(result) && IS_INT(car(head))) {
      result = DOUBLE_VALUE(AS_DOUBLE(result)
                            + AS_DOUBLE(CAST_INT_TO_DOUBLE(car(head))));
    } else {
      result = INT_VALUE(AS_INT(result) + AS_INT(car(head)));
    }

    head = cdr(head);
  }

  return result;
 return result;
}
