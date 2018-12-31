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
}

Value minus(Value args) {
  Value head = cdr(args);
  Value result = car(args);
  while (!IS_NULL(head)) {
    if (IS_INT(result) && IS_DOUBLE(car(head))) {
      result = CAST_INT_TO_DOUBLE(result);
    }

    if (IS_DOUBLE(result) && IS_DOUBLE(car(head))) {
      result = DOUBLE_VALUE(AS_DOUBLE(result)
                            - AS_DOUBLE(car(head)));
    } else if (IS_DOUBLE(result) && IS_INT(car(head))) {
      result = DOUBLE_VALUE(AS_DOUBLE(result)
                            - AS_DOUBLE(CAST_INT_TO_DOUBLE(car(head))));
    } else {
      result = INT_VALUE(AS_INT(result) - AS_INT(car(head)));
    }

    head = cdr(head);
  }

  return result;
}

Value nEqual(Value args) {
  Value head = cdr(args);
  Value result; 

  Value firstValue = car(args);

  if (IS_INT(firstValue)) {
    result = CAST_INT_TO_DOUBLE(firstValue);
  } else {
    result = firstValue;
  }
  
  while (!IS_NULL(head)) {
    if (IS_DOUBLE(car(head))) {
      if (AS_DOUBLE(result) != AS_DOUBLE(car(head))) {
        return BOOL_VALUE(false);
      }
    } else {
      if (AS_DOUBLE(result) != AS_INT(car(head))) {
        return BOOL_VALUE(false);
      }
    }

    head = cdr(head);
  }

  return BOOL_VALUE(true);
}
