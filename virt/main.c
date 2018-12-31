#include <stdio.h>
#include <stdlib.h>
#include "opCodes.h"

#include "interpret.h"
#include "constants.h"
#include "pairMemory.h"
#include "symboltable.h"
#include "value.h"

void printBinary(int i) {
    for (int bit = 0; bit < 8; bit++)
        putchar(i & (1 << bit) ? '1' : '0');
}

int main() {
    initMemory();
    initSymbolTable();
    initInterpreter();

    //inputConstant(0, INT_VALUE(3));
    //inputConstant(1, INT_VALUE(2));
    //inputConstant(2, INT_VALUE(1));

    /*
       LoadInstruction load[7] = {
       { INPUT, 0, INT_VALUE(1) },
       { INPUT, 1, DOUBLE_VALUE(1.1) },
       { INPUT, 2, INT_VALUE(2) },
       { INPUT, 3, SYMBOL_VALUE("n") },
       { INPUT, 4, cons(SYMBOL_VALUE("n"), NIL_VALUE) },
       { INPUT, 5, BOOL_VALUE(true) },
       { END_INPUT,  },
       };
       LoadInstruction load[50] = { { INPUT, 0, INT_VALUE(3) },
       { INPUT, 1, INT_VALUE(2) },
       { INPUT, 2, INT_VALUE(1) },
       { INPUT, 3, SYMBOL_VALUE("some_symbol") },
       { END_INPUT } };

       static Operation arr[50] = { { LOAD, VAL_REG, 0 },
       { LIST, ARGL_REG, VAL_REG },
       { LOAD, VAL_REG, 1 },
       { CONS, ARGL_REG, VAL_REG, ARGL_REG },
       { LOAD, VAL_REG, 2 },
       { CONS, ARGL_REG, VAL_REG, ARGL_REG },
       { ADD, VAL_REG, ARGL_REG,  },
       { DISPLAY, VAL_REG },
       { END } };
     */

    LoadInstruction load[24] = {
        { INPUT, 0, cons(SYMBOL_VALUE("f"), NIL_VALUE) },
        { INPUT, 1, cons(SYMBOL_VALUE("x"), NIL_VALUE) },
        { INPUT, 2, SYMBOL_VALUE("f") },
        { INPUT, 3, cons(SYMBOL_VALUE("y"), NIL_VALUE) },
        { INPUT, 4, SYMBOL_VALUE("x") },
        { INPUT, 5, SYMBOL_VALUE("x") },
        { INPUT, 6, SYMBOL_VALUE("y") },
        { INPUT, 7, cons(SYMBOL_VALUE("x"), NIL_VALUE) },
        { INPUT, 8, SYMBOL_VALUE("f") },
        { INPUT, 9, cons(SYMBOL_VALUE("y"), NIL_VALUE) },
        { INPUT, 10, SYMBOL_VALUE("x") },
        { INPUT, 11, SYMBOL_VALUE("x") },
        { INPUT, 12, SYMBOL_VALUE("y") },
        { INPUT, 13, cons(SYMBOL_VALUE("f"), NIL_VALUE) },
        { INPUT, 14, cons(SYMBOL_VALUE("n"), NIL_VALUE) },
        { INPUT, 15, INT_VALUE(0) },
        { INPUT, 16, SYMBOL_VALUE("n") },
        { INPUT, 17, INT_VALUE(1) },
        { INPUT, 18, SYMBOL_VALUE("f") },
        { INPUT, 19, INT_VALUE(1) },
        { INPUT, 20, SYMBOL_VALUE("n") },
        { INPUT, 21, SYMBOL_VALUE("n") },
        { INPUT, 22, INT_VALUE(1) },
        { END_INPUT,  },
    };

    static Operation arr[134] = {
        { MKPROC, PROC_REG, 2,  },
        { GOTO, 76,  },
        { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG,  },
        { LOAD, TMP_REG, 0,  },
        { EXTND, TMP_REG, ARGL_REG,  },
        { MKPROC, PROC_REG, 7,  },
        { GOTO, 39,  },
        { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG,  },
        { LOAD, TMP_REG, 1,  },
        { EXTND, TMP_REG, ARGL_REG,  },
        { LOAD, TMP_REG, 2,  },
        { LOOKUP, PROC_REG, TMP_REG,  },
        { MKPROC, VAL_REG, 14,  },
        { GOTO, 36,  },
        { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG,  },
        { LOAD, TMP_REG, 3,  },
        { EXTND, TMP_REG, ARGL_REG,  },
        { SAVE, CONTINUE_REG,  },
        { SAVE, ENV_REG,  },
        { LOAD, TMP_REG, 4,  },
        { LOOKUP, PROC_REG, TMP_REG,  },
        { LOAD, TMP_REG, 5,  },
        { LOOKUP, VAL_REG, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { ASSIGN_CONTINUE, 27,  },
        { COMPILED_PROC_ENTRY, TMP_REG, PROC_REG,  },
        { JUMP, TMP_REG,  },
        { ASSIGN, PROC_REG, VAL_REG,  },
        { GOTO, 29,  },
        { RESTORE, ENV_REG,  },
        { RESTORE, CONTINUE_REG,  },
        { LOAD, TMP_REG, 6,  },
        { LOOKUP, VAL_REG, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { COMPILED_PROC_ENTRY, VAL_REG, PROC_REG,  },
        { JUMP, VAL_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { COMPILED_PROC_ENTRY, VAL_REG, PROC_REG,  },
        { JUMP, VAL_REG,  },
        { MKPROC, VAL_REG, 41,  },
        { GOTO, 73,  },
        { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG,  },
        { LOAD, TMP_REG, 7,  },
        { EXTND, TMP_REG, ARGL_REG,  },
        { LOAD, TMP_REG, 8,  },
        { LOOKUP, PROC_REG, TMP_REG,  },
        { MKPROC, VAL_REG, 48,  },
        { GOTO, 70,  },
        { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG,  },
        { LOAD, TMP_REG, 9,  },
        { EXTND, TMP_REG, ARGL_REG,  },
        { SAVE, CONTINUE_REG,  },
        { SAVE, ENV_REG,  },
        { LOAD, TMP_REG, 10,  },
        { LOOKUP, PROC_REG, TMP_REG,  },
        { LOAD, TMP_REG, 11,  },
        { LOOKUP, VAL_REG, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { ASSIGN_CONTINUE, 61,  },
        { COMPILED_PROC_ENTRY, TMP_REG, PROC_REG,  },
        { JUMP, TMP_REG,  },
        { ASSIGN, PROC_REG, VAL_REG,  },
        { GOTO, 63,  },
        { RESTORE, ENV_REG,  },
        { RESTORE, CONTINUE_REG,  },
        { LOAD, TMP_REG, 12,  },
        { LOOKUP, VAL_REG, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { COMPILED_PROC_ENTRY, VAL_REG, PROC_REG,  },
        { JUMP, VAL_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { COMPILED_PROC_ENTRY, VAL_REG, PROC_REG,  },
        { JUMP, VAL_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { COMPILED_PROC_ENTRY, VAL_REG, PROC_REG,  },
        { JUMP, VAL_REG,  },
        { MKPROC, VAL_REG, 78,  },
        { GOTO, 120,  },
        { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG,  },
        { LOAD, TMP_REG, 13,  },
        { EXTND, TMP_REG, ARGL_REG,  },
        { MKPROC, VAL_REG, 83,  },
        { JUMP, CONTINUE_REG,  },
        { COMPILED_PROCEDURE_ENV, ENV_REG, PROC_REG,  },
        { LOAD, TMP_REG, 14,  },
        { EXTND, TMP_REG, ARGL_REG,  },
        { LOAD, TMP_REG, 15,  },
        { ASSIGN, VAL_REG, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { LOAD, TMP_REG, 16,  },
        { LOOKUP, VAL_REG, TMP_REG,  },
        { CONS, ARGL_REG, VAL_REG, ARGL_REG,  },
        { EQ, VAL_REG, ARGL_REG,  },
        { TEST, VAL_REG, 97,  },
        { LOAD, TMP_REG, 17,  },
        { ASSIGN, VAL_REG, TMP_REG,  },
        { JUMP, CONTINUE_REG,  },
        { SAVE, CONTINUE_REG,  },
        { SAVE, ENV_REG,  },
        { LOAD, TMP_REG, 18,  },
        { LOOKUP, PROC_REG, TMP_REG,  },
        { LOAD, TMP_REG, 19,  },
        { ASSIGN, VAL_REG, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { LOAD, TMP_REG, 20,  },
        { LOOKUP, VAL_REG, TMP_REG,  },
        { CONS, ARGL_REG, VAL_REG, ARGL_REG,  },
        { MINUS, VAL_REG, ARGL_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { ASSIGN_CONTINUE, 112,  },
        { COMPILED_PROC_ENTRY, TMP_REG, PROC_REG,  },
        { JUMP, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { RESTORE, ENV_REG,  },
        { LOAD, TMP_REG, 21,  },
        { LOOKUP, VAL_REG, TMP_REG,  },
        { CONS, ARGL_REG, VAL_REG, ARGL_REG,  },
        { RESTORE, CONTINUE_REG,  },
        { MULT, VAL_REG, ARGL_REG,  },
        { JUMP, CONTINUE_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { ASSIGN_CONTINUE, 124,  },
        { COMPILED_PROC_ENTRY, TMP_REG, PROC_REG,  },
        { JUMP, TMP_REG,  },
        { ASSIGN, PROC_REG, VAL_REG,  },
        { GOTO, 126,  },
        { LOAD, TMP_REG, 22,  },
        { ASSIGN, VAL_REG, TMP_REG,  },
        { LIST, ARGL_REG, VAL_REG,  },
        { ASSIGN_CONTINUE, 132,  },
        { COMPILED_PROC_ENTRY, TMP_REG, PROC_REG,  },
        { JUMP, TMP_REG,  },
        { DISPLAY, VAL_REG },
        { END,  },
    };

    /*
       static Operation arr[50] = { { LOAD, ARGL_REG, 0x1 },
       { LOAD, VAL_REG, 0x0 },
       { ASSIGN, TMP_REG, N1 },
       { EQUAL_VALUE, TMP_REG, ARGL_REG, TMP_REG },
       { TEST, TMP_REG, 0x6 },
       { GOTO,  0xE },
       { LIST, VAL_REG, VAL_REG },
       { CONS, VAL_REG, ARGL_REG, VAL_REG },
       { MULT, VAL_REG, VAL_REG },
       { LIST, ARGL_REG, ARGL_REG },
       { LOAD, TMP_REG, 0x2 },
       { LIST, TMP_REG, VAL_REG },
       { ASSIGN, ARGL_REG, TMP_REG },
       { LOOKUP, VAL_REG, 0, },
       { CONS, TMP_REG, VAL_REG, ARGL_REG },
       { ASSIGN, ARGL_REG, TMP_REG },
       { ADD, TMP_REG, ARGL_REG, },
       { ASSIGN, VAL_REG, TMP_REG, },
       { JUMP, CONT_REG, },
       { LOAD, VAL_REG, 1 },
       { LIST, TMP_REG, VAL_REG, },
       { ASSIGN, ARGL_REG, TMP_REG },
       { ASSIGN_CONTINUE, 19 },
       { JUMP, PROC_REG },
       };
     */

    /*
       static Operation arr[50] = { { LOAD, ARGL_REG, 0x0},
       { LIST, ARGL_REG, ARGL_REG },
       { LOAD, VAL_REG, 0x1 },
       { LIST, VAL_REG, VAL_REG },
       { EXTND, ARGL_REG, VAL_REG },
       { LOAD, ARGL_REG, 0x0 },
       { LOOKUP, TMP_REG, ARGL_REG },
       { DISPLAY, TMP_REG },
       { END } };

     */

    int i = 0;
    while (i == 0 || arr[i - 1].op != END) {
        Operation op = arr[i];
        printBinary(op.op);
        printBinary(op.dest);
        printBinary(op.arg1);
        printBinary(op.arg2);
        putchar('\n');
        i++;
    }

    loadConstants(load);
    interpret(arr);
    printf("\nDONE\n");
}
