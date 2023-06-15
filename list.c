#include "list.h"

#include <assert.h>
#include <stdlib.h>

#define CAPACITY_GROWTH 5

List list_create(int capacity, ListFf free_function) {
  List l = malloc(sizeof(struct List));
  assert(l != NULL);

  l->arr = malloc(capacity * sizeof(void *));
  assert(l->arr != NULL);
  l->len = 0;
  l->cap = capacity;
  l->ff = free_function;
  return l;
}

void list_free(List l) {
  if (l->ff != NULL) {
    for (int i = 0; i < l->len; i++) {
      (*l->ff)(l->arr[i]);
    }
  }
  free(l->arr);
  free(l);
}

static void grow(List l) {
  if (l->len + 1 >= l->cap) {
    l->cap += CAPACITY_GROWTH;
    l->arr = realloc(l->arr, l->cap * sizeof(void *));
    assert(l->arr != NULL);
  }
}

void *list_get(List l, int idx) {
  if (idx < 0 || idx >= l->len) {
    return NULL;
  }
  return l->arr[idx];
}

void list_push(List l, void *element) {
  grow(l);
  l->arr[l->len++] = element;
}

void *list_remove(List l, int idx) {
  if (idx < 0 || idx >= l->len) {
    return NULL;
  }
  void *element = l->arr[idx];
  for (int i = idx + 1; i < l->len; i++) {
    l->arr[i - 1] = l->arr[i];
  }
  l->len--;

  return element;
}

bool list_empty(List l) {
  return l->len == 0;
}

