#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "raylib.h"

struct asteroid {
  double size;
  Vector2 position;
  double speed;
  double rotation;
};
typedef struct asteroid *asteroid;

extern asteroid *create_asteroids(int n);

extern void free_asteroids(asteroid *as);

extern void draw_asteroids(asteroid *as);

extern void move_asteroids(asteroid *as);

#endif

