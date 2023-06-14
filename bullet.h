#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

typedef double degrees;

typedef struct{
  Vector2 pos;       // float x, float y
  double radius;
  double speed;
  degrees direction; // counterclockwise from horizontal, left to right is 0
  Color color;       // char r, g, b, a 
} Bullet;

/**
 * Returns a pointer to an initialised bullet with the specified parameters.
 * 
 * @param pos A Vector2 representing position of the bullet.
 * @param radius A float representing the radius of the bullet.
 * @param speed A float representing the 
 * @param direction 
 * @param color 
 * @return The pointer to the initalised bullet.
 */
extern Bullet *bullet_init(Vector2 pos, double radius, double speed, degrees direction, Color color);


extern void bullet_free(Bullet *b);
extern void bullet_draw(Bullet b);
extern void bullet_move(Bullet *b);

#endif
