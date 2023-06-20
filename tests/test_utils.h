#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdbool.h>

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

#endif

