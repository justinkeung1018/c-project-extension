#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "dynarr.h"
#include "raylib.h"

struct Asteroid {
  double size;
  Vector2 position;
  double speed;
  double rotation;
};
typedef struct Asteroid *Asteroid;

/**
 * Initialises the asteroids.
 *
 * @return Dynamic Array of asteroids.
 */
extern dynarr asteroids_create(void);

/**
 * Frees the asteroids.
 *
 * @param as Dynamic Array of asteroids to free.
 */
extern void asteroids_free(dynarr as);

/**
 * Draws the asteroids.
 *
 * @param as Dynamic Array of asteroids to draw.
 */
extern void asteroids_draw(dynarr as);

/**
 * Moves the asteroids. To be called each action frame.
 *
 * @param as Dynamic Array of asteroids to move.
 */
extern void asteroids_move(dynarr as);

#endif

