#ifndef UTILS_H
#define UTILS_H

// Macros
#define NUM_ELEMENTS(arr) ((sizeof(arr) / sizeof(arr[0])))
#define RADIANS(x)        (x * M_PI / 180)

typedef struct {
  Vector2 *vectors;
  int length;
} Collider;

#endif

