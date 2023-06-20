#include "bullet.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "raylib.h"

#define INITIAL_SIZE  256
#define NORMAL_RADIUS 5
#define NORMAL_SPEED  25
#define NORMAL_COLOUR RED

static Bullet bullet_init(float pos_x, float pos_y, float radius, float speed, Radians rotation, Color color) {
  Bullet b = malloc(sizeof(struct Bullet));

  if (b == NULL) {
    fprintf(stderr, "Failed to malloc bullet\n");
    exit(EXIT_FAILURE);
  }

  b->pos.x = pos_x;
  b->pos.y = pos_y;
  b->radius = radius;
  b->speed = speed;
  b->rotation = rotation;
  b->color = color;
  return b;
}

typedef void (*ForEachFunc)(Bullet);

// Caller must free using bullet_free()
Bullet bullet_init(float pos_x, float pos_y, Radians rotation) {
  return bullet_init(pos_x, pos_y, NORMAL_RADIUS, NORMAL_SPEED, rotation, NORMAL_COLOUR);
}

void bullet_free(void *b) {
  free((Bullet)b);
}

void bullet_draw(Bullet b) {
  DrawCircleV(b->pos, b->radius, b->color);
}

void bullet_move(Bullet b) {
  b->pos.x += cos(b->rotation) * b->speed;
  b->pos.y += sin(b->rotation) * b->speed;
}

static void bullet_for_each_void(List bs, ForEachFunc function) {
  for (int i = 0; i < bs->len; i++) {
    function((Bullet)list_get(bs, i));
  }
}

void bullet_draw_all(List bs) {
  bullet_for_each_void(bs, bullet_draw);
}

void bullet_move_all(List bs) {
  bullet_for_each_void(bs, bullet_move);
}

List bullet_init_all() {
  return list_create(INITIAL_SIZE, bullet_free);
}

bool bullet_in_screen(Bullet b) {
  return 0 <= b->pos.x && b->pos.x <= GetScreenWidth() && 0 <= b->pos.y && b->pos.y <= GetScreenHeight();
}

void bullet_despawn_all_off_screen(List bs) {
  for (int i = bs->len - 1; i >= 0; i--) {
    Bullet b = (Bullet)list_get(bs, i);
    if (!bullet_in_screen(b)) {
      list_remove(bs, i);
      bullet_free(b);
    }
  }
}

void bullet_free_all(List bs) {
  list_free(bs);
}

