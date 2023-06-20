#ifndef BULLET_H
#define BULLET_H

#include "list.h"
#include "raylib.h"

typedef double Radians;

struct Bullet {
  Vector2 pos;       // float x, float y
  double radius;
  double speed;
  Radians rotation;  // clockwise from horizontal, positive x-axis is 0
  Color color;       // char r, g, b, a
};

typedef struct Bullet *Bullet;

/**
 * Returns a bullet with the specified parameters.
 * Must be freed.
 *
 * @param pos_x A float representing the x position of the bullet.
 * @param pos_y A float representing the y position of the bullet.
 * @param rotation Rotation in radians, clockwise from horizontal, positive x-axis is 0.
 *
 * @return A bullet.
 */
extern Bullet bullet_init(float pos_x, float pos_y, Radians rotation);

/**
 * Frees a bullet pointer.
 *
 * @param b The pointer to the bullet to be freed.
 */
extern void bullet_free(void *b);

/**
 * Draws a bullet. Assumes caller has BeginDrawing() before calling and will
 * EndDrawing() after.
 *
 * @param b The pointer to the bullet to be drawn.
 */
extern void bullet_draw(Bullet b);

/**
 * Moves a bullet according to its position, speed, rotation.
 *
 * @param b The pointer to the bullet being moved.
 */
extern void bullet_move(Bullet b);

/**
 * Draws all bullets in bs.
 *
 * @param bs A list containing all bullets.
 */
extern void bullet_draw_all(List bs);

/**
 * Moves all bullets in bs, according to their position, speed, rotation.
 *
 * @param bs A list containing all bullets.
 */
extern void bullet_move_all(List bs);

/**
 * Creates a list capable of containing bullets.
 *
 * @return The list.
 */
extern List bullet_init_all();

/**
 * Checks if a bullet is on screen or not.
 *
 * @param b The pointer to the bullet.
 *
 * @return Whether the bullet is on screen.
 */
extern bool bullet_in_screen(Bullet b);

/**
 * Removes any bullet not on screen from the list and frees it.
 *
 * @param bs The list of bullets.
 */
extern void bullet_despawn_all_off_screen(List bs);

/**
 * Frees the given list of bullets.
 *
 * @param bs The list with all bullets to be freed.
 */
extern void bullet_free_all(List bs);

#endif

