#include "bullet.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

// Caller must free using bullet_free()
Bullet *bullet_init(Vector2 pos, double radius, double speed, degrees direction, Color color) {
  Bullet *b = malloc(sizeof(Bullet));
  
  if (b == NULL) {
    fprintf(stderr, "Failed to malloc bullet");
    exit(EXIT_FAILURE);
  }

  b->pos = pos;
  b->radius = radius;
  b->speed = speed;
  b->direction = direction;
  b->color = color;
  return b;
}

void bullet_free(Bullet *b) {
  free(b);
}

void bullet_draw(Bullet b) {
  BeginDrawing();

    DrawCircleV(b.pos, b.radius, b.color);

  EndDrawing();
}

void bullet_move(Bullet *b) {
  b->pos.x += cos(b->direction);
  b->pos.y += sin(b->direction); 
}


