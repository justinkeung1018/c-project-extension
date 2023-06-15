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

/**
 * Creates a dynamic array.
 * 
 * @param capacity The initial capacity of the dynamic array.
 * @param free_function The function that frees the dynamic array.
 *
 * @return The dynamic array.
 */
extern dynarr dynarr_create(int capacity, dynarr_ff free_function);

/**
 * Frees the dynamic array.
 * 
 * @param da The dynamic array to free.
 */
extern void dynarr_free(dynarr da);

/**
 * Gets an element from the dynamic array.
 * 
 * @param da The dynamic array to get element from.
 * @param idx The index of the element to get.
 * 
 * @return A void pointer to the element.
 */
extern void *dynarr_get(dynarr da, int idx);

/**
 * Pushes an element to the dynamic array.
 * 
 * @param da The dynamic array to push the element to.
 * @param element void pointer to the element to push.
 */
extern void dynarr_push(dynarr da, void *element);

/**
 * Removes an element at a specified index from the dynamic array.
 * 
 * @param da The dynamic array to remove the element from.
 * @param idx The index of the element to remove.
 */
extern void dynarr_remove(dynarr da, int idx);

#endif

