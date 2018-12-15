#ifndef scheme_op_code_h
#define scheme_op_code_h

typedef enum {
  ASSIGN = 0,
  TEST,
  GOTO,
  LOAD,
  CONS,
  LIST,
  ADD,
  MULT,
  DISPLAY,
  END,
  EQUAL_VALUE,
} OpCode;

typedef enum {
  NO_REGISTER,
  N0,
  N1,
  N2,
  TMP_REG,
  VAL_REG,
  ARGL_REG,
} Dest;


typedef struct {
  OpCode op;
  Dest dest;
  Dest arg1;
  Dest arg2;
} Operation;

#endif

/** Instruction Set:
    - N0     DEST   ----
    - N1     DEST   ----
    - N2     DEST   ----

    - ADD    DEST   ARGL
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
    - DISP   ----   SRC

    - TEST   ----   REG    LABEL

    - GOTO   ----   LABEL
    - PUSH   ----   ARG
    - POP    DEST   ----

    - LOOKUP DEST   INDEX
    - DEFINE ----   INDEX   VALUE
    - SET    ----   INDEX   VALUE

    - END    ----   -----   -----

    - PREDICATES
 **/
