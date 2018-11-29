#ifndef scheme_compiler_h
#define scheme_compiler_h

#include <stdbool.h>

#include "vm.h"
#include "parsetree.h"

bool compile(ParseNode parseNode, Chunk *chunk);

#endif
