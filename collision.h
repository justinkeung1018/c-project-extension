#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "raylib.h"

typedef struct {
  Vector2 *vectors;
  int length;
} Collider;

struct Asteroid;
typedef struct Asteroid *Asteroid;

struct Bullet;
typedef struct Bullet *Bullet;

struct Spaceship;
typedef struct Spaceship *Spaceship;

/**
 * Determines if the asteroid collides with the spaceship.
 *
 * @param a The asteroid.
 * @param s The spaceship.
 *
 * @return Whether the asteroid collides with the spaceship.
 */
extern bool collides_asteroid_spaceship(Asteroid a, Spaceship s);

/**
 * Determines if the bullet hits the asteroid.
 *
 * @param a The asteroid.
 * @param b The bullet.
 *
 * @return Whether the bullet hits the asteroid.
 */
extern bool collides_asteroid_bullet(Asteroid a, Bullet b);

#endif

