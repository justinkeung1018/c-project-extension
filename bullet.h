#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "dynarr.h"

typedef double degrees;

typedef struct{
  Vector2 pos;       // float x, float y
  double radius;
  double speed;
  degrees direction; // clockwise from horizontal, left to right is 0
  Color color;       // char r, g, b, a 
} Bullet;

/**
 * Returns a pointer to an initialised bullet with the specified parameters.
 * Must be freed.
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

/**
 * Frees a bullet pointer.  
 * 
 * @param b The pointer to the bullet to be freed.
 */
extern void bullet_free(Bullet *b);

/**
 * Draws a bullet. Assumes caller has BeginDrawing() before calling and will 
 * EndDrawing() after.
 * 
 * @param b The pointer to the bullet to be drawn.
 */
extern void bullet_draw(Bullet *b);

/**
 * Moves a bullet according to its position, speed, direction.
 * 
 * @param b The pointer to the bullet being moved.
 */
extern void bullet_move(Bullet *b);

/**
 * Draws all bullets in bs.
 * 
 * @param bs A dynarr containing all bullets.
 */
extern void bullet_draw_all(dynarr bs);

/**
 * Moves all bullets in bs, according to their position, speed, direction.
 * 
 * @param bs A dynarr containing all bullets.
 */
extern void bullet_move_all(dynarr bs);

#endif
