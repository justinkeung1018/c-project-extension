#include "test_asteroid.h"
#include "test_bullet.h"
#include "test_collision.h"
#include "test_spaceship.h"
#include "test_list.h"

int main(void) {
  test_collides_asteroid_spaceship();
  test_collides_asteroid_bullet();
  test_spaceship_rotate_left();
  test_spaceship_rotate_right();
  test_spaceship_accelerate();
  test_spaceship_move();
  test_spaceship_shoot();
  test_bullet_move();
  test_bullet_move_all();
  test_bullet_in_screen();
  test_bullet_despawn_all_off_screen();
  test_asteroid_move_all();
  test_asteroid_break();
  test_list();
  return 0;
}

