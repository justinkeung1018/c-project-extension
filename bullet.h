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
 * @param pos_x A float representing the x position of the bullet.
 * @param pos_y A float representing the y position of the bullet.
 * @param radius A float representing the radius of the bullet.
 * @param speed A float representing the 
 * @param direction 
 * @param color 
 * @return The pointer to the initalised bullet.
 */
extern Bullet *bullet_init(float pos_x, float pos_y, double radius, double speed, degrees direction, Color color);


extern void bullet_free(Bullet *b);
extern void bullet_draw(Bullet *b);
extern void bullet_move(Bullet *b);

#endif
