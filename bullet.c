#include "bullet.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

// Caller must free using bullet_free()
Bullet *bullet_init(float pos_x, float pos_y, double radius, double speed, degrees direction, Color color) {
  Bullet *b = malloc(sizeof(Bullet));
  
  if (b == NULL) {
    fprintf(stderr, "Failed to malloc bullet");
    exit(EXIT_FAILURE);
  }

  b->pos.x = pos_x;
  b->pos.y = pos_y;
  b->radius = radius;
  b->speed = speed;
  b->direction = direction;
  b->color = color;
  return b;
}

void bullet_free(Bullet *b) {
  free(b);
}

void bullet_draw(Bullet *b) {
  BeginDrawing();
    DrawCircleV(b->pos, b->radius, b->color);
  EndDrawing();
}

static float deg_to_rad(degrees deg) {
  return deg / 180 * M_PI;
}

void bullet_move(Bullet *b) {
  b->pos.x += cos(deg_to_rad(b->direction)) * b->speed * 100 * GetFrameTime();
  b->pos.y += sin(deg_to_rad(b->direction)) * b->speed * 100 * GetFrameTime(); 
}


