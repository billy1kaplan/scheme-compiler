#ifndef scheme_op_code_h
#define scheme_op_code_h

typedef enum {
  ASSIGN,
  LOAD,
  CONS,
  LIST,
  ADD,
  MULT,
  DISPLAY,
} OpCode;

typedef enum {
  N0,
  N1,
  N2,
  NO_REGISTER,
  VAL,
  ARGL,
} Modifier;

typedef struct {
  OpCode op;
  Modifier dest;
  Modifier arg1;
  Modifier arg2;
} Operation;

#endif

/** Instruction Set:
    - N0     DEST
    - N1     DEST
    - N2     DEST
    - ADD    DEST   ARGL
    - SUB    DEST   ARGL
    - MULT   DEST   ARGL
    - DIV    DEST   ARGL
    - ASSIGN DEST   SRC
    - CONS   DEST   ARG1   ARG2
    - LIST   DEST   ARGL
    - DISP   ----   ARGL
    - TEST   DEST   PRED   REG
    - GOTO   DEST   <- Line Number
    - PUSH   ----   ARG
    - POP    DEST   ----

    - LOOKUP DEST   INDEX
    - DEFINE ----   INDEX   VALUE
    - SET    ----   INDEX   VALUE

    - PREDICATES
 **/
