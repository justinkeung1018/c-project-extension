#include "spaceship.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bullet.h"
#include "list.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"

#define SPACESHIP_HEIGHT   200
#define SPACESHIP_WIDTH    100
#define COEFF_FRICTION     0.01

#define ACCELERATION_STEP  0.1
#define ROTATION_STEP      10

#define MIN_SPEED          0
#define MAX_SPEED          10
#define MIN_ACCELERATION   0
#define MAX_ACCELERATION   0.3
#define MIN_ROTATION       0
#define MAX_ROTATION       (2 * M_PI)

static Vector2 get_top(Spaceship s) {
  Vector2 top_offset = Vector2Rotate((Vector2){ 0, -SPACESHIP_HEIGHT * 2 / 3 }, s->rotation);
  return Vector2Add(s->position, top_offset);
}

static Vector2 get_left(Spaceship s) {
  Vector2 left_offset = Vector2Rotate((Vector2){ -SPACESHIP_WIDTH / 2, 0 }, s->rotation);
  return Vector2Add(s->position, left_offset);
}

static Vector2 get_right(Spaceship s) {
  Vector2 right_offset = Vector2Rotate((Vector2){ SPACESHIP_WIDTH / 2, 0 }, s->rotation);
  return Vector2Add(s->position, right_offset);
}

static void update_collider(Spaceship s) {
  s->collider.vectors[0] = get_top(s);
  s->collider.vectors[1] = get_left(s);
  s->collider.vectors[2] = get_right(s);
}

Spaceship spaceship_initialise(void) {
  Spaceship s = malloc(sizeof(struct Spaceship));
  if (s == NULL) {
    fprintf(stderr, "Memory allocation for spaceship failed.\n");
    exit(EXIT_FAILURE);
  }

  s->position = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2 };
  s->velocity = (Vector2){ 0, 0 };

  Vector2 *vectors = malloc(sizeof(Vector2) * 3);
  s->collider = (Collider){ vectors, 3 };
  update_collider(s);

  s->acceleration = 0.0;
  s->rotation = 0.0;
  s->color = RED;

  return s;
}

void spaceship_free(Spaceship s) {
  free(s->collider.vectors);
  free(s);
}

void spaceship_move(Spaceship s) {
  Vector2 acceleration_vector = (Vector2){ s->acceleration * sin(s->rotation), -(s->acceleration * cos(s->rotation)) };
  s->velocity = Vector2Add(s->velocity, acceleration_vector);
  s->velocity = Vector2ClampValue(s->velocity, MIN_SPEED, MAX_SPEED);

  Vector2 friction = (Vector2){ -s->velocity.x * COEFF_FRICTION, -s->velocity.y * COEFF_FRICTION };
  s->velocity = Vector2Add(s->velocity, friction);

  s->position.x = Clamp(s->position.x + s->velocity.x, 0, GetScreenWidth());
  s->position.y = Clamp(s->position.y + s->velocity.y, 0, GetScreenHeight());

  update_collider(s);
}

void spaceship_draw(Spaceship s) {
  DrawTriangle(
      s->collider.vectors[0], // Top
      s->collider.vectors[1], // Left
      s->collider.vectors[2], // Right
      s->color
    );
}

void spaceship_accelerate(Spaceship s) {
  s->acceleration += ACCELERATION_STEP;
  s->acceleration = Clamp(s->acceleration, MIN_ACCELERATION, MAX_ACCELERATION);
}

void spaceship_reset_acceleration(Spaceship s) {
  s->acceleration = 0;
}

void spaceship_rotate_left(Spaceship s) {
  s->rotation -= RADIANS(ROTATION_STEP);
  s->rotation = Wrap(s->rotation, MIN_ROTATION, MAX_ROTATION);
}

void spaceship_rotate_right(Spaceship s) {
  s->rotation += RADIANS(ROTATION_STEP);
  s->rotation = Wrap(s->rotation, MIN_ROTATION, MAX_ROTATION);
}

void spaceship_shoot(Spaceship s, List bs) {
  Vector2 tip = Vector2Add(s->position, Vector2Rotate((Vector2){ 0, -SPACESHIP_HEIGHT * 2 / 3 }, s->rotation));
  list_push(bs, bullet_init(tip.x, tip.y, s->rotation - M_PI_2));
}

