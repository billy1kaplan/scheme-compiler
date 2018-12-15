#include <stdio.h>

#include "constants.h"
#include "operations.h"
#include "pairMemory.h"
#include "value.h"

void testInt(char *msg, int expected, int actual) {
  if (actual == expected) {
    printf(".");
  } else {
    printf("x\n\nTest Failed: %s. Expected: %i Actual: %i\n\n", msg, expected, actual);
  }
}

void testFloat(char *msg, double expected, double actual) {
  if (actual == expected) {
    printf(".");
  } else {
    printf("x\n\nTest Failed: %s. Expected %f Actual: %f\n\n", msg, expected, actual);
  }
}

void test_identity_product() {
  Value args = NIL_VALUE;
  int expected = 1;
  int actual = AS_INT(product(args));
  testInt("Product of nothing is identity", expected, actual);
}

void test_single_product() {
  Value args = cons(INT_VALUE(5), NIL_VALUE);
  int expected = 5;
  int actual = AS_INT(product(args));
  testInt("5 * 1 = 5", expected, actual);
}

void test_single_float() {
  Value args = cons(DOUBLE_VALUE(5.5), NIL_VALUE);
  double expected = 5.5;
  double actual = AS_DOUBLE(product(args));
  testFloat("5.5 * 1 = 5.5", expected, actual);
}

void test_simple_product() {
  Value args = cons(TWO, cons(TWO, NIL_VALUE));
  int expected = 4;
  int actual = AS_INT(product(args));
  testInt("2 * 2 = 4", expected, actual);
}

void test_simple_float_product() {
  Value args = cons(DOUBLE_VALUE(2.5), cons(DOUBLE_VALUE(3.0), NIL_VALUE));
  double expected = 2.5 * 3.0;
  double actual = AS_DOUBLE(product(args));
  testFloat("2.5 * 3.0 = 7.5", expected, actual);
}

void test_mixed_type_product() {
  Value args = cons(INT_VALUE(2), cons(DOUBLE_VALUE(3.5), NIL_VALUE));
  double expected = 2 * 3.5;
  double actual = AS_DOUBLE(product(args));
  testFloat("2 * 3.5 = 7.0", expected, actual);
}

void test_identity_sum() {
  Value args = NIL_VALUE;
  int expected = 0;
  int actual = AS_INT(sum(args));
  testInt("Sum of 0 is 0", expected, actual);
}

void test_single_sum() {
  Value args = cons(INT_VALUE(7), NIL_VALUE);
  int expected = 7;
  int actual = AS_INT(sum(args));
  testInt("0 + 7 = 7", expected, actual);
}

void test_single_float_sum() {
  Value args = cons(DOUBLE_VALUE(5.51), NIL_VALUE);
  double expected = 5.51;
  double actual = AS_DOUBLE(sum(args));
  testFloat("0 + 5.51 = 5.51", expected, actual);
}

void test_simple_sum() {
  Value args = cons(TWO, cons(INT_VALUE(8), NIL_VALUE));
  int expected = 2 + 8;
  int actual = AS_INT(sum(args));
  testInt("2 + 8 = 10", expected, actual);
}

void test_simple_float_sum() {
  Value args = cons(DOUBLE_VALUE(2.5), cons(DOUBLE_VALUE(3.0), NIL_VALUE));
  double expected = 2.5 + 3.0;
  double actual = AS_DOUBLE(sum(args));
  testFloat("2.5 + 3.0 = 5.5", expected, actual);
}

void test_mixed_type_sum() {
  Value args = cons(INT_VALUE(2), cons(DOUBLE_VALUE(3.5), NIL_VALUE));
  double expected = 2 + 3.5;
  double actual = AS_DOUBLE(sum(args));
  testFloat("2 + 3.5 = 5.5", expected, actual);
}

int main() {
  // test product
  test_identity_product();
  test_single_product();
  test_single_float();
  test_simple_product();
  test_simple_float_product();
  test_mixed_type_product();

  // test sum
  test_identity_sum();
  test_single_sum();
  test_single_float_sum();
  test_simple_sum();
  test_simple_float_sum();
  test_mixed_type_sum();
}
