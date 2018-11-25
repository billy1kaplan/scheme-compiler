#include "parser.h"
#include "parsetree.h"
#include <stdio.h>

int main() {
  ParseNode *result = parse();
  display(result);
  printf("\n");
  cleanupParseNode(result);
}
