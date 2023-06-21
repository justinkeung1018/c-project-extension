#include "player.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "raylib.h"

Player player_initialise(
    Spaceship s,
    List bs,
    int key_up,
    int key_left,
    int key_right,
    int key_shoot,
    Sound shoot_sound
  ) {
  Player player = malloc(sizeof(struct Player));
  assert(player != NULL);

  player->s = s;
  player->bs = bs;
  player->key_up = key_up;
  player->key_left = key_left;
  player->key_right = key_right;
  player->key_shoot = key_shoot;
  player->shoot_sound = shoot_sound;

  return player;
}

bool player_check_collision(Player player, List as) {
  for (int i = 0; i < list_length(as); i++) {
    Asteroid a = list_get(as, i);
    if (collides_asteroid_spaceship(a, player->s)) {
      return true;
    }

    bool asteroid_broken = false;
    for (int j = 0; j < list_length(player->bs); j++) {
      Bullet b = list_get(player->bs, j);
      if (collides_asteroid_bullet(a, b)) {
        if (!asteroid_broken) {
          // Handle edge case where multiple bullets collide with the same asteroid
          // to avoid breaking the same asteroid more than once
          asteroid_break(as, i);
          asteroid_broken = true;
        }
        list_remove(player->bs, j);
        bullet_free(b);
      }
    }
  }

  return false;
}

void player_control(Player player, bool can_shoot) {
  if (IsKeyDown(player->key_shoot) && can_shoot) {
    spaceship_shoot(player->s, player->bs);
    PlaySound(player->shoot_sound);
  }

  if (IsKeyDown(player->key_up)) {
    spaceship_accelerate(player->s);
  } else {
    spaceship_reset_acceleration(player->s);
  }

  if (IsKeyDown(player->key_left)) {
    spaceship_rotate_left(player->s);
  }

  if (IsKeyDown(player->key_right)) {
    spaceship_rotate_right(player->s);
  }
}

void player_despawn_all_off_screen(Player player) {
  bullet_despawn_all_off_screen(player->bs);
}

void player_move(Player player) {
  spaceship_move(player->s);
  bullet_move_all(player->bs);
}

void player_draw(Player player) {
  spaceship_draw(player->s);
  bullet_draw_all(player->bs);
}

void player_free(void *player) {
  spaceship_free(((Player)player)->s);
  bullet_free_all(((Player)player)->bs);
}

