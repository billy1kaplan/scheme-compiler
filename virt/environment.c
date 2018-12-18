#include <stdio.h>

#include "environment.h"

static bool hasEnclosingEnvironment(Environment env) {
  return env.enclosingEnvironment != NULL;
}

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


Value lookupSymbolEnv(Value sym, Environment env) {
  Environment curEnv = env;
  Value result = assoc(sym, curEnv.values);

  while (IS_NULL(result) && hasEnclosingEnvironment(curEnv)) {
    curEnv = *curEnv.enclosingEnvironment;
    result = assoc(sym, curEnv.values);
  }

    if (IS_PAIR(result)) {
      return cdr(result);
    } else {
      return result;
    }
}

Environment extendEnvironment(Value values, Value variables, Environment *env) {
  Value frame = NIL_VALUE;

  Value curValues = values;
  Value curVariables = variables;
  while (IS_PAIR(curValues) && IS_PAIR(curVariables)) {
    frame = cons(car(curVariables), car(curValues));
    curValues = cdr(curValues);
    curVariables = cdr(curVariables);
  }

  return WRAP_ENV(frame, env);
}
