#include "test_utils.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "raylib.h"
#include "raymath.h"

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

void assert_eq_int(int expected, int result, const char *testname) {
  if (expected != result) {
    printf("%-*s: expected %d, actual %d\n", WIDTH, testname, expected, result);
  } else {
    printf("%-*s: OK\n", WIDTH, testname);
  }
}

void assert_eq_double(double expected, double result, const char *testname) {
  if (!FloatEquals(expected, result)) {
    printf("%-*s: expected %lf, actual %lf\n", WIDTH, testname, expected, result);
  } else {
    printf("%-*s: OK\n", WIDTH, testname);
  }
}

void assert_eq_double_arr(double expected[], double result[], int arr_length, const char *testname) {
  int count_failed = 0;
  for (int i = 0; i < arr_length; i++) {
    if (!FloatEquals(expected[i], result[i])) {
      printf("%-*s: expected %lf, actual %lf, case %d\n", WIDTH, testname, expected[i], result[i], i);
      count_failed++;
    }
  }

  if (count_failed == 0) {
    printf("%-*s: OK\n", WIDTH, testname);
  } 
}

void assert_eq_Vector2(Vector2 expected, Vector2 result, const char *testname) {
  if (!Vector2Equals(expected, result)) {
    printf("%-*s: expected x = %lf and y = %lf, got x = %lf and y = %lf.\n", WIDTH, testname, expected.x, expected.y, result.x, result.y);
  } else {
    printf("%-*s: OK\n", WIDTH, testname);
  }
}

void assert_eq_Vector2_arr(Vector2 expected[], Vector2 result[], int arr_length, const char *testname) {
  int count_failed = 0;
  for (int i = 0; i < arr_length; i++) {
    if (!Vector2Equals(expected[i], result[i])) {
      printf("%-*s: expected x = %lf and y = %lf, got x = %lf and y = %lf, case %d\n", WIDTH, testname, expected[i].x, expected[i].y, result[i].x, result[i].y, i);
      count_failed++;
    }
  }

  if (count_failed == 0) {
    printf("%-*s: OK\n", WIDTH, testname);
  } 
}

