#include "test_utils.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "raylib.h"

#define WIDTH 60
#define EPSILON 0.0000001

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

void assert_eq_int(int expected, int result, const char *testname) {
  if (expected != result) {
    printf("%-*s: expected %d, actual %d\n", WIDTH, testname, expected, result);
  } else {
    printf("%-*s: OK\n", WIDTH, testname);
  }
}

void assert_eq_double(double expected, double result, const char *testname) {
  if (fabs(result - expected) >= EPSILON) {
    printf("%-*s: expected %lf, actual %lf\n", WIDTH, testname, expected, result);
  } else {
    printf("%-*s: OK\n", WIDTH, testname);
  }
}

void assert_eq_Vector2(Vector2 expected, Vector2 result, const char *testname) {
  if (fabs(result.x - expected.x) >= EPSILON && fabs(result.y - expected.y) >= EPSILON) {
    printf("%-*s: expected x = %lf and y = %lf, got x = %lf and y = %lf.\n", WIDTH, testname, expected.x, expected.y, result.x, result.y);
  } else {
    printf("%-*s: OK\n", WIDTH, testname);
  }
}