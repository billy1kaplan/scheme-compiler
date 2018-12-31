#ifndef scheme_environment_h
#define scheme_environment_h

#include <stdbool.h>
#include <stdlib.h>

#include "pairMemory.h"

Value lookupSymbolEnv(Value sym, Value env);
Value extendEnvironment(Value values, Value variables, Value env);
void displayEnvironment(Value env);

// Line number + Environment
// E.g. (cons lineNumber env)
#define MAKE_PROC(value, env) (cons(value, env))

#define GET_PROC_LABEL(proc) (car(proc))
#define GET_PROC_ENV(proc) (cdr(proc))

#define BASE_ENV (NIL_VALUE)

#endif
