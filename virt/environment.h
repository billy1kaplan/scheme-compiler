#ifndef scheme_environment_h
#define scheme_environment_h

#include <stdbool.h>
#include <stdlib.h>

#include "pairMemory.h"

typedef struct Environment {
  Value values;
  struct Environment *enclosingEnvironment;
} tEnvironment;

typedef struct Environment Environment;

Environment baseEnvironment();

Value lookupSymbolEnv(Value sym, Environment env);
Environment extendEnvironment(Value values, Value variables, Environment *env);

typedef struct closure {
  Value body;
  Environment env;
} Closure;

#define IS_CLOSURE(value) ((value).type == CLOSURE)

#define CLOSURE_VALUE(value, env) ((Value) { CLOSURE, .as.closure = &(Closure) { (value), (env) }})

#define GET_CLOSURE_BODY(closure) ((closure).as.closure->body)
#define GET_CLOSURE_ENV(closure) ((closure).as.closure->env)

#define WRAP_ENV(frame, enclosingEnvironment) ((Environment){ frame, enclosingEnvironment })
#define BASE_ENV ((Environment){ NIL_VALUE, NULL })


#endif
