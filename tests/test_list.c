#include "test_list.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include "test_utils.h"
#include "utils.h"

#define NUM_OBJECTS 500

struct MockObject {
  int value;
};

typedef struct MockObject *MockObject;

static MockObject mock_object_create(int value) {
  MockObject object = malloc(sizeof(struct MockObject));
  assert(object != NULL);
  object->value = value;
  return object;
}

static void mock_object_free(void *element) {
  free((MockObject)element);
}

static void populate(List l) {
  for (int i = 0; i < NUM_OBJECTS; i++) {
    MockObject mo = mock_object_create(i);
    list_push(l, mo);
  }
}

static void test_list_initialise(void) {
  List l = list_create(NUM_OBJECTS, mock_object_free);
  bool correct_init = true;

  correct_init = correct_init && l != NULL;
  correct_init = correct_init && l->len == 0;
  correct_init = correct_init && l->cap == NUM_OBJECTS;
  correct_init = correct_init && l->ff == mock_object_free;

  assert_true(correct_init, __func__);

  list_free(l);
}

static void test_list_grow(void) {
  int original_cap = 1;

  List l = list_create(original_cap, mock_object_free);

  populate(l);

  bool pushed_all = l->len == NUM_OBJECTS;
  bool grew = original_cap < l->cap && l->cap > NUM_OBJECTS;

  assert_true(pushed_all && grew, __func__);

  list_free(l);
}

static void test_list_push_number(void) {
  bool correct_number = true;

  List l = list_create(NUM_OBJECTS, mock_object_free);

  for (int i = 1; i < NUM_OBJECTS; i++) {
    MockObject mo = mock_object_create(i);
    list_push(l, mo);
    correct_number = correct_number && l->len == i;
  }

  assert_true(correct_number, __func__);

  list_free(l);
}

static void test_list_push_order(void) {
  bool correct_order = true;

  List l = list_create(NUM_OBJECTS, mock_object_free);

  for (int i = 0; i < NUM_OBJECTS; i++) {
    MockObject mo = mock_object_create(i);
    list_push(l, mo);
    correct_order = correct_order && ((MockObject)list_get(l, i))->value == i;
  }

  assert_true(correct_order, __func__);

  list_free(l);
}

static void test_list_get(void) {
  bool correct_get = true;

  List l = list_create(NUM_OBJECTS, mock_object_free);
  MockObject mos[NUM_OBJECTS];

  for (int i = 0; i < NUM_OBJECTS; i++) {
    MockObject mo = mock_object_create(i);
    list_push(l, mo);
    mos[i] = mo;
  }

  for (int i = 0; i < NUM_OBJECTS; i++) {
    correct_get = correct_get && mos[i] == list_get(l, i);
  }

  assert_true(correct_get, __func__);

  list_free(l);
}

static void test_list_remove(void) {
  bool correct_remove = true;

  List l = list_create(NUM_OBJECTS, mock_object_free);

  populate(l);

  int remove[] = {0, 10, 50, 345, 495};

  for (int i = 0; i < NUM_ELEMENTS(remove); i++) {
    correct_remove = correct_remove && ((MockObject)list_remove(l, remove[i]))->value - i == remove[i];
  }

  correct_remove = correct_remove && l->len == NUM_OBJECTS - 5;

  for (int i = 0; i < l->len; i++) {
    for (int j = 0; j < NUM_ELEMENTS(remove); j++) {
      if (((MockObject)list_get(l, i))->value == remove[j] + j) {
        correct_remove = false;
      }
    }
  }

  assert_true(correct_remove, __func__);

  list_free(l);
}

static void test_list_length(void) {
  List l = list_create(NUM_OBJECTS, mock_object_free);

  populate(l);

  bool correct_length = list_length(l) == NUM_OBJECTS;

  for (int i = NUM_OBJECTS; i < 2 * NUM_OBJECTS; i++) {
    MockObject mo = mock_object_create(i);
    list_push(l, mo);
  }

  correct_length = correct_length && list_length(l) == 2 * NUM_OBJECTS;

  assert_true(correct_length, __func__);

  list_free(l);
}

static void test_list_empty(void) {
  List l = list_create(NUM_OBJECTS, mock_object_free);

  bool correct_empty = list_empty(l);

  MockObject mo = mock_object_create(0);
  list_push(l, mo);

  correct_empty = correct_empty && !list_empty(l);

  assert_true(correct_empty, __func__);

  list_free(l);
}

void test_list(void) {
  test_list_initialise();
  test_list_grow();
  test_list_push_number();
  test_list_push_order();
  test_list_get();
  test_list_remove();
  test_list_length();
  test_list_empty();
}

