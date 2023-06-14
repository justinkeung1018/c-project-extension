#include "spaceship.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define SPACESHIP_HEIGHT 100
#define SPACESHIP_WIDTH  50
#define ACCELERATION_STEP  0.3 
#define DECELERATION_STEP  0.3
#define ROTATION_STEP      20 

#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)
#define RADIANS(x) (x * M_PI / 180)

Spaceship *spaceship_initialise(void) {
  Spaceship *spaceship = malloc(sizeof(Spaceship));
  if (spaceship == NULL) {
    fprintf(stderr, "Memory allocation for spaceship failed.\n");
    exit(EXIT_FAILURE);
  }

  spaceship->position = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2 };
  spaceship->speed = 0.0;
  spaceship->acceleration = 0.0;
  spaceship->rotation = 0.0;
  spaceship->color = RED;

  return spaceship;
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

static void update_state(Spaceship *spaceship) {
  spaceship->speed = MAX(MIN(spaceship->speed + spaceship->acceleration, 5), 0);
  spaceship->position.x += spaceship->speed * sin(spaceship->rotation);
  spaceship->position.y -= spaceship->speed * cos(spaceship->rotation);
}

void spaceship_draw(Spaceship *spaceship) {
  update_state(spaceship);

  Vector2 top = rotate((Vector2){ 0, -SPACESHIP_HEIGHT * 2 / 3 }, spaceship->rotation);
  Vector2 left = rotate((Vector2){ -SPACESHIP_WIDTH / 2, 0 }, spaceship->rotation);
  Vector2 right = rotate((Vector2){ SPACESHIP_WIDTH / 2, 0 }, spaceship->rotation);

  /*
  Vector2 top = (Vector2){
      spaceship->position.x - SPACESHIP_HEIGHT / 2 * sin(spaceship->rotation),
      spaceship->position.y + SPACESHIP_HEIGHT / 2 * cos(spaceship->rotation),
    };
  Vector2 left = (Vector2){
      spaceship->position.x - SPACESHIP_WIDTH / 2 * cos(spaceship->rotation),
      spaceship->position.y + SPACESHIP_HEIGHT / 2 * sin(spaceship->rotation),
    };
  Vector2 right = (Vector2){
      spaceship->position.x - SPACESHIP_WIDTH / 2 * cos(spaceship->rotation),
      spaceship->position.y - SPACESHIP_HEIGHT / 2 * sin(spaceship->rotation),
    };
  */

  DrawTriangle(
      add_vector(spaceship->position, top),
      add_vector(spaceship->position, left),
      add_vector(spaceship->position, right),
      spaceship->color
    );
}

void spaceship_accelerate(Spaceship *spaceship) {
  spaceship->acceleration += ACCELERATION_STEP;
}

void spaceship_decelerate(Spaceship *spaceship) {
  spaceship->acceleration -= DECELERATION_STEP;
}

void spaceship_rotate_left(Spaceship *spaceship) {
  spaceship->rotation += RADIANS(ROTATION_STEP);
}

void spaceship_rotate_right(Spaceship *spaceship) {
  spaceship->rotation -= RADIANS(ROTATION_STEP);
}

