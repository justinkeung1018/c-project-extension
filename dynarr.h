#ifndef DYNARR_H
#define DYNARR_H

typedef void (*dynarr_ff)(void *element);

struct dynarr {
  void **arr;
  int len;
  int cap;
  dynarr_ff ff;
};
typedef struct dynarr *dynarr;

extern dynarr dynarr_create(int capacity, dynarr_ff free_function);

extern void dynarr_free(dynarr da);

extern void *dynarr_get(dynarr da, int idx);

extern void dynarr_set(dynarr da, int idx, void *element);

extern void dynarr_push(dynarr da, void *element);

extern void dynarr_remove(dynarr da, int idx);

#endif

