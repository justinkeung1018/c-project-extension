#ifndef ASTEROID_H
#define ASTEROID_H

#include "list.h"
#include "raylib.h"

struct Asteroid {
  double size;
  Vector2 position;
  Vector2 velocity;
};

typedef struct Asteroid *Asteroid;

/**
 * Initialises the asteroids.
 *
 * @return Dynamic array of asteroids.
 */
extern List asteroid_create_all(void);

/**
 * Frees the asteroids.
 *
 * @param as Dynamic array of asteroids to free.
 */
extern void asteroid_free_all(List as);

/**
 * Draws the asteroids.
 *
 * @param as Dynamic array of asteroids to draw.
 */
extern void asteroid_draw_all(List as);

/**
 * Moves the asteroids. To be called each action frame.
 *
 * @param as Dynamic array of asteroids to move.
 */
extern void asteroid_move_all(List as);

/**
 * Breaks the asteroid into two. If it cannot be broken further, it is removed.
 *
 * @param as Dynamic array of asteroids.
 * @param idx The index of the asteroid to break.
 */
extern void asteroid_break(List as, int idx);

#endif

