#ifndef scheme_op_code_h
#define scheme_op_code_h

#include "value.h"

typedef enum {
  ASSIGN = 0,
  TEST,
  GOTO,
  LOAD,
  CONS,
  LIST,
  ADD,
  MINUS,
  MULT,
  DISPLAY,
  END,
  EQUAL_VALUE,
  EXTND,
  LOOKUP,
  MKPROC,
  SAVE,
  RESTORE,
  ASSIGN_CONTINUE,
  COMPILED_PROC_ENTRY,
  COMPILED_PROCEDURE_ENV,
  JUMP,
  EQ,
} OpCode;

typedef enum {
  INPUT,
  END_INPUT
} LoadOp;

typedef struct {
  LoadOp op;
  int index;
  Value value;
} LoadInstruction;

typedef enum {
  VAL_REG = 0,
  ARGL_REG,
  TMP_REG,
  CONTINUE_REG,
  PROC_REG,
  ENV_REG,
} Dest;


typedef struct {
  OpCode op;
  Dest dest;
  Dest arg1;
  Dest arg2;
} Operation;

#endif

/** Instruction Set:
DONE    - N0     DEST   ----
DONE    - N1     DEST   ----
DONE    - N2     DEST   ----

DONE    - ADD    DEST   ARGL
    - SUB    DEST   ARGL
    - MULT   DEST   ARGL
    - DIV    DEST   ARGL
    - NEGATE DEST   ARGL
    - RECIP  DEST   ARGL

    - EQ     DEST   ARG1   ARG2
    - LT     DEST   ARG1   ARG2
    - GT     DEST   ARG1   ARG2

    - ASSIGN DEST   SRC
    - LOAD   DEST   LOC

    - CONS   DEST   ARG1   ARG2
    - LIST   DEST   ARGL
    - DISP   SRC

    - TEST   REG    LABEL

    - GOTO   LABEL
    - SAVE    DEST
    - RESTORE DEST

    - LOOKUP DEST   INDEX
    - DEFINE ----   INDEX   VALUE
    - SET    ----   INDEX   VALUE

    - END    ----   -----   -----

    - EXTND  VARS    VALS <- Places into env register
    - LOOKUP DEST   VAR
    - CLSR   DEST   BODY

    - LAMBDA DEST   BODY    ARGS

    - PREDICATES
 **/
