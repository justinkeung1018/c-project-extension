#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "asteroid.h"
#include "bullet.h"
#include "spaceship.h"

struct Player {
  Spaceship s;
  List bs;
  int key_up;
  int key_left;
  int key_right;
  int key_shoot;
  Sound shoot_sound;
};

typedef struct Player *Player;

/**
 * Initialises a player.
 *
 * @param s The spaceship.
 * @param bs The list of bullets.
 * @param key_up The key to accelerate the spaceship.
 * @param key_left The key to rotate the spaceship left.
 * @param key_right The key to rotate the spaceship right.
 * @param key_shoot The key to shoot bullets from the spaceship.
 * @param shoot_sound The sound when shooting a bullet.
 *
 * @return The player.
 */
extern Player player_initialise(
    Spaceship s,
    List bs,
    int key_up,
    int key_left,
    int key_right,
    int key_shoot,
    Sound shoot
  );

/**
 * Checks if the spaceship collides with an asteroid, or if a bullet hits an asteroid.
 * If any such collision occurs, update the state of the game accordingly.
 *
 * @param player The player.
 * @param as The list of asteroids.
 * @param score The current score.
 *
 * @return Whether the game should terminate.
 */
extern bool player_check_collision(Player player, List as, int *score);

/**
 * Updates the player state based on the keyboard input.
 *
 * @param player The player.
 * @param can_shoot Whether the player is allowed to shoot at this frame.
 */
extern void player_control(Player player, bool can_shoot);

/**
 * Despawns all entities related to the player that are off screen.
 *
 * @param player The player.
 */
extern void player_despawn_all_off_screen(Player player);

/**
 * Moves the player.
 *
 * @param player The player.
 */
extern void player_move(Player player);

/**
 * Draws the player.
 *
 * @param player The player.
 */
extern void player_draw(Player player);

/**
 * Frees the player.
 *
 * @param The player.
 */
extern void player_free(void *player);

#endif

