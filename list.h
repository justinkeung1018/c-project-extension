#ifndef DYNARR_H
#define DYNARR_H

#include <stdbool.h>

typedef void (*ListFf)(void *element);

struct List {
  void **arr;
  int len;
  int cap;
  ListFf ff;
};

typedef struct List *List;

/**
 * Creates a resizable list.
 * 
 * @param capacity The initial capacity of the list.
 * @param free_function The function that frees the list.
 *
 * @return The list.
 */
extern List list_create(int capacity, ListFf free_function);

/**
 * Frees the list.
 * 
 * @param l The list to free.
 */
extern void list_free(List l);

/**
 * Gets an element from the list.
 * 
 * @param l The list to get element from.
 * @param idx The index of the element to get.
 * 
 * @return A void pointer to the element.
 */
extern void *list_get(List l, int idx);

/**
 * Pushes an element to the list.
 * 
 * @param l The list to push the element to.
 * @param element void pointer to the element to push.
 */
extern void list_push(List l, void *element);

/**
 * Removes an element at a specified index from the list.
 * 
 * @param l The list to remove the element from.
 * @param idx The index of the element to remove.
 *
 * @return The element removed.
 */
extern void *list_remove(List l, int idx);

/**
 * Checks if the list is empty
 * 
 * @param l The list to check.
 *
 * @return True if empty, false otherwise.
 */
extern bool list_empty(List l);

#endif

