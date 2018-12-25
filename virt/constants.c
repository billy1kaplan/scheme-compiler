#include "constants.h"

ConstantsTable constantsTable;

void inputConstant(int index, Value value) {
  constantsTable.constants[index] = value;
}

Value retrieveConstant(int index) {
  return constantsTable.constants[index];
}
