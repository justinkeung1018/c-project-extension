#include "test_utils.h"

#include <stdbool.h>
#include <stdio.h>

#define WIDTH 60

static char *boolstr(bool expr) {
  return expr ? "true" : "false";
}

void assert_true(bool expr, const char *testname) {
  if (expr) {
    printf("%-*s: OK\n", WIDTH, testname);
  } else {
    printf("%-*s: expected %s, actual %s\n", WIDTH, testname, boolstr(!expr), boolstr(expr));
  }
}

void assert_false(bool expr, const char *testname) {
  if (expr) {
    printf("%-*s: expected %s, actual %s\n", WIDTH, testname, boolstr(!expr), boolstr(expr));
  } else {
    printf("%-*s: OK\n", WIDTH, testname);
  }
}

