#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "list.h"
#include "raylib.h"

struct Spaceship {
  Vector2 position;
  Vector2 velocity;
  double acceleration;
  double rotation;
  Color color;
};

typedef struct Spaceship *Spaceship;

/**
 * Initialises the spaceship.
 *
 * @return The initial spaceship.
 */
extern Spaceship spaceship_initialise(void);

/**
 * Frees the spaceship.
 *
 * @param s The spaceship.
 */
extern void spaceship_free(Spaceship s);

/**
 * Moves the spaceship to its new state after each frame.
 *
 * @param s The spaceship.
 */
extern void spaceship_move(Spaceship s);

/**
 * Draws the spaceship.
 *
 * @param s The spaceship.
 */
extern void spaceship_draw(Spaceship s);

/**
 * Accelerates the spaceship.
 *
 * @param s The spaceship.
 */
extern void spaceship_accelerate(Spaceship s);

/**
 * Sets the acceleration of the spaceship to 0.
 *
 * @param s The spaceship.
 */
extern void spaceship_reset_acceleration(Spaceship s);

/**
 * Rotates the spaceship left.
 *
 * @param s The spaceship.
 */
extern void spaceship_rotate_left(Spaceship s);

/**
 * Rotates the spaceship right.
 *
 * @param s The spaceship.
 */
extern void spaceship_rotate_right(Spaceship s);

/**
 * Shoots a bullet from the spaceship. Adds the bullet to the list.
 *
 * @param s The spaceship.
 * @param bullets The list of bullets.
 */
extern void spaceship_shoot(Spaceship s, List bs);

#endif

