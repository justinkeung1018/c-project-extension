#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"

typedef struct {
  Vector2 position;
  Vector2 velocity;
  double acceleration;
  double rotation;
  Color color;
} Spaceship;

/**
 * Initialises the spaceship.
 *
 * @return The initial spaceship.
 */
extern Spaceship *spaceship_initialise(void);

/**
 * Draws the spaceship.
 *
 * @param The spaceship.
 */
extern void spaceship_draw(Spaceship *spaceship);

/**
 * Accelerates the spaceship.
 *
 * @param The spaceship.
 */
extern void spaceship_accelerate(Spaceship *spaceship);

/**
 * Decelerates the spaceship.
 *
 * @param The spaceship.
 */
extern void spaceship_decelerate(Spaceship *spaceship);

/**
 * Rotates the spaceship left.
 *
 * @param The spaceship.
 */
extern void spaceship_rotate_left(Spaceship *spaceship);

/**
 * Rotates the spaceship right.
 *
 * @param The spaceship.
 */
extern void spaceship_rotate_right(Spaceship *spaceship);

#endif

