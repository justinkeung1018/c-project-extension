#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "raylib.h"
#include "dynarr.h"

struct asteroid {
  double size;
  Vector2 position;
  double speed;
  double rotation;
};
typedef struct asteroid *asteroid;

extern dynarr create_asteroids(void);

extern void free_asteroids(dynarr as);

extern void draw_asteroids(dynarr as);

extern void move_asteroids(dynarr as);

#endif

