typedef struct {
  int count;
  int capacity;
  ValueArray *symbols;
} Frame;

typedef struct {
  int count;
  int capacity;
  struct Frame *frames;
} Environment;

typedef struct {
  int frame;
  int symbolLocation;
} EnvLocation;

typedef struct {
  EnvLocation symbolLocation;
  struct ProcArg *next;
} ProcArg;

//Symbol Table:
//Symbol -> (Frame, Location)

// Environment structure is statically determinable (which frames go where), the values used are not

void initEnvironment(Environment *env);
void freeEnvironment(Environment *env);
void defineVariableInFrame(int location, Frame *frame);
void defineVariable(EnvLocation envLocation, Value value, Environment *env);
void setVariable(EnvLocation envLocation, Value value, Environment *env);
Value lookupVariable(EnvLocation location, Environment *env);
void extendEnvironment(ProcArg args, Value bindings, Environment *env);

