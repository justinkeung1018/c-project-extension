#include "spaceship.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define SPACESHIP_HEIGHT   200
#define SPACESHIP_WIDTH    100
#define COEFF_FRICTION     0.01

#define ACCELERATION_STEP  0.1
#define DECELERATION_STEP  0.3
#define ROTATION_STEP      10

#define MIN_SPEED          0
#define MAX_SPEED          10
#define MIN_ACCELERATION   (-10)
#define MAX_ACCELERATION   0.3

// Macros
#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)
#define RADIANS(x) (x * M_PI / 180)

Spaceship *spaceship_initialise(void) {
  Spaceship *s = malloc(sizeof(Spaceship));
  if (s == NULL) {
    fprintf(stderr, "Memory allocation for spaceship failed.\n");
    exit(EXIT_FAILURE);
  }

  s->position = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2 };
  s->velocity = (Vector2){ 0, 0 };
  s->acceleration = 0.2;
  s->rotation = 0.0;
  s->color = RED;

  return s;
}

void spaceship_free(Spaceship *spaceship) {
  free(spaceship);
}

static Vector2 rotate(Vector2 vector, double radians) {
  Vector2 rotated_vector = vector;
  rotated_vector.x = vector.x * cos(radians) - vector.y * sin(radians);
  rotated_vector.y = vector.x * sin(radians) + vector.y * cos(radians);
  return rotated_vector;
}

static Vector2 add_vector(Vector2 v1, Vector2 v2) {
  return (Vector2){ v1.x + v2.x, v1.y + v2.y };
}

static double clamp(double value, double lo, double hi) {
  return MIN(MAX(value, lo), hi);
}

static double get_magnitude(Vector2 vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y);
}

static Vector2 clamp_vector(Vector2 vector, double lo_magnitude, double hi_magnitude) {
  Vector2 clamped_vector = vector;

  double magnitude = get_magnitude(vector);

  if (magnitude == 0) {
    return clamped_vector;
  }

  double clamped_magnitude = clamp(magnitude, lo_magnitude, hi_magnitude);

  clamped_vector.x = clamped_vector.x / magnitude * clamped_magnitude;
  clamped_vector.y = clamped_vector.y / magnitude * clamped_magnitude;

  return clamped_vector;
}

static void update_state(Spaceship *s) {
  Vector2 acceleration_vector = (Vector2){ s->acceleration * sin(s->rotation), -(s->acceleration * cos(s->rotation)) };
  s->velocity = add_vector(s->velocity, acceleration_vector);
  s->velocity = clamp_vector(s->velocity, MIN_SPEED, MAX_SPEED);

  Vector2 friction = (Vector2){ -s->velocity.x * COEFF_FRICTION, -s->velocity.y * COEFF_FRICTION };
  s->velocity = add_vector(s->velocity, friction);

  s->position.x = clamp(s->position.x + s->velocity.x, 0, GetScreenWidth());
  s->position.y = clamp(s->position.y + s->velocity.y, 0, GetScreenHeight());
}

void spaceship_draw(Spaceship *s) {
  update_state(s);

  Vector2 top = rotate((Vector2){ 0, -SPACESHIP_HEIGHT * 2 / 3 }, s->rotation);
  Vector2 left = rotate((Vector2){ -SPACESHIP_WIDTH / 2, 0 }, s->rotation);
  Vector2 right = rotate((Vector2){ SPACESHIP_WIDTH / 2, 0 }, s->rotation);

  DrawTriangle(
      add_vector(s->position, top),
      add_vector(s->position, left),
      add_vector(s->position, right),
      s->color
    );
}

void spaceship_accelerate(Spaceship *s) {
  s->acceleration += ACCELERATION_STEP;
  s->acceleration = clamp(s->acceleration, MIN_ACCELERATION, MAX_ACCELERATION);
}

void spaceship_decelerate(Spaceship *s) {
  s->acceleration -= DECELERATION_STEP;
  s->acceleration = clamp(s->acceleration, MIN_ACCELERATION, MAX_ACCELERATION);
}

void spaceship_rotate_left(Spaceship *s) {
  s->rotation -= RADIANS(ROTATION_STEP);
}

void spaceship_rotate_right(Spaceship *s) {
  s->rotation += RADIANS(ROTATION_STEP);
}

