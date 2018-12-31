#include <stdio.h>

#include "environment.h"

static Value assoc(Value sym, Value values) {
  Value head = values;

  while (IS_PAIR(head)) {
    if (isEqualValue(sym, car(head))) {
      return cons(sym, cdr(head));
    }
    head = cdr(head);
  }

  return NIL_VALUE;
}


Value lookupSymbolEnv(Value sym, Value env) {
  Value head = env;
  Value result = assoc(sym, env);

  while (!IS_NULL(head)) {
    result = assoc(sym, car(head));

    if (!IS_NULL(result))
      break;

    head = cdr(head);
  }

    if (IS_PAIR(result)) {
      return cdr(result);
    } else {
      return result;
    }
}

Value extendEnvironment(Value values, Value variables, Value env) {
  Value frame = NIL_VALUE;

  Value curValues = values;
  Value curVariables = variables;
  while (IS_PAIR(curValues) && IS_PAIR(curVariables)) {
    frame = cons(car(curVariables), car(curValues));
    curValues = cdr(curValues);
    curVariables = cdr(curVariables);
  }

  return cons(frame, env);
}

void displayEnvironment(Value env) {
  displayValue(env);
}
