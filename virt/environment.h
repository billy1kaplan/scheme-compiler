#ifndef scheme_environment_h
#define scheme_environment_h

#include <stdbool.h>
#include <stdlib.h>

#include "pairMemory.h"

typedef struct {
  Value frames;
} Environment ;

Value lookupSymbolEnv(Value sym, Environment env);
Environment extendEnvironment(Value values, Value variables, Environment env);
void displayEnvironment(Environment env);

typedef struct proc {
  int lineNumber;
  Environment env;
} Proc;

#define IS_PROC(value) ((value).type == PROC)

#define MAKE_PROC(value, env) ((Value) { PROC, .as.proc = &(Proc) { (value), (env) }})

#define GET_PROC_ENV(closure) ((closure).as.proc->env)
#define GET_PROC_LABEL(closure) ((closure).as.proc->lineNumber)

#define BASE_ENV ((Environment){ NIL_VALUE })
#define WRAP_ENV(vals) ((Environment){ (vals) })

#endif
