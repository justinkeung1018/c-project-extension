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

/**
 * Initialises the asteroids.
 *
 * @return Dynamic Array of asteroids.
 */
extern dynarr create_asteroids(void);

/**
 * Frees the asteroids.
 */
extern void free_asteroids(dynarr as);

/**
 * Draws the asteroids.
 */
extern void draw_asteroids(dynarr as);

/**
 * Moves the asteroids. To be called each action frame.
 */
extern void move_asteroids(dynarr as);

#endif

