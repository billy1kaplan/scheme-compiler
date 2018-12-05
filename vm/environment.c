#include "environment.h"

void initEnvironment(Environment *env) {
  env->count = 0;
  env->capacity = 0;
  env->frames = NULL;
}

void freeEnvironment(Environment *env) {
  FREE_ARRAY(struct Frame, env->frames, env->capacity);
}

void defineVariable(Environment *env, EnvLocation envLocation, Value value) {

}

void setVariable(EnvLocation envLocation, Value value, Environment *env);

Value lookupVariable(EnvLocation location, Environment *env);

void extendEnvironment(ProcArg args, Value bindings, Environment *env);
