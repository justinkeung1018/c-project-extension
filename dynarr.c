#include "dynarr.h"

#include <assert.h>
#include <stdlib.h>

#define CAPACITY_GROWTH 5

dynarr dynarr_create(int capacity, dynarr_ff free_function) {
  dynarr da = malloc(sizeof(struct dynarr));
  assert(da != NULL);

  da->arr = malloc(capacity * sizeof(void *));
  assert(da->arr != NULL);
  da->len = 0;
  da->cap = capacity;
  da->ff = free_function;
  return da;
}

void dynarr_free(dynarr da) {
  if (da->ff != NULL) {
    for (int i = 0; i < da->len; i++) {
      (*da->ff)(da->arr[i]);
    }
  }
  free(da->arr);
  free(da);
}

static void grow(dynarr da) {
  if (da->len + 1 >= da->cap) {
    da->cap += CAPACITY_GROWTH;
    da->arr = realloc(da->arr, da->cap * sizeof(void *));
    assert(da->arr != NULL);
  }
}

void *dynarr_get(dynarr da, int idx) {
  if (idx < 0 || idx >= da->len) {
    return NULL;
  }
  return da->arr[idx];
}

void dynarr_push(dynarr da, void *element) {
  grow(da);
  da->arr[da->len++] = element;
}

void dynarr_remove(dynarr da, int idx) {
  if (idx < 0 || idx >= da->len) {
    return;
  }
  for (int i = idx + 1; i < da->len; i++) {
    da[i - 1] = da[i];
  }
  da->len--;
}

