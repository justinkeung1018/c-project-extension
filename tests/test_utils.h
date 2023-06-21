#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdbool.h>

#include "raylib.h"

/**
 * Asserts the expression evaluates to true.
 *
 * @param expr The Boolean expression.
 * @param testname The name of the test.
 */
extern void assert_true(bool expr, const char *testname);

/**
 * Asserts the expression evaluates to false.
 *
 * @param expr The Boolean expression.
 * @param testname The name of the test.
 */
extern void assert_false(bool expr, const char *testname);

/**
 * Asserts an int value is equal to the expected int value. 
 * 
 * @param expected The expected int. 
 * @param result The int to be tested. 
 * @param testname The name of the test.
 */
extern void assert_eq_int(int expected, int result, const char *testname); 

/**
 * Asserts a double value is equal to the expected double value. 
 * 
 * @param expected The expected double. 
 * @param result The double to be tested. 
 * @param testname The name of the test.
 */
extern void assert_eq_double(double expected, double result, const char *testname); 

/**
 * Asserts the contents of each index in the result double array is equal to the 
 * contents in the expected double array 
 * 
 * @param expected The expected double array. 
 * @param result The double array to be tested. 
 * @param arr_length The length of the arrays.
 * @param testname The name of the test.
 */
extern void assert_eq_double_arr(double expected[], double result[], int arr_length, const char *testname);

/**
 * Asserts a Vector2 value is equal to the expected Vector2 value. 
 * 
 * @param expected The expected Vector2. 
 * @param result The Vector2 to be tested. 
 * @param testname The name of the test.
 */
extern void assert_eq_Vector2(Vector2 expected, Vector2 result, const char *testname); 

/**
 * Asserts the contents of each index in the result Vector2 array is equal to the 
 * contents in the expected Vector2 array 
 * 
 * @param expected The expected Vector2 array. 
 * @param result The Vector2 array to be tested. 
 * @param arr_length The length of the arrays.
 * @param testname The name of the test.
 */
extern void assert_eq_Vector2_arr(Vector2 expected[], Vector2 result[], int arr_length, const char *testname);

#endif

