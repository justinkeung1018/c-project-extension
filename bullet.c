#include "bullet.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "raylib.h"

#define INITIAL_SIZE 256
#define NORMAL_RADIUS 5
#define NORMAL_SPEED 25
#define NORMAL_COLOUR RED
#define RADIANS(x) (x * M_PI / 180)

// Caller must free using bullet_free()
static Bullet bullet_init(float pos_x, float pos_y, float radius, float speed, degrees direction, Color color) {
  Bullet b = malloc(sizeof(struct Bullet));

  if (b == NULL) {
    fprintf(stderr, "Failed to malloc bullet\n");
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

typedef void (*ForEachFunc)(Bullet);

// Caller must free using bullet_free()
Bullet bullet_init_normal(float pos_x, float pos_y, degrees direction) {
  return bullet_init(pos_x, pos_y, NORMAL_RADIUS, NORMAL_SPEED, direction, NORMAL_COLOUR);
}

void bullet_free(void *b) {
  free((Bullet) b);
}

void bullet_draw(Bullet b) {
  DrawCircleV(b->pos, b->radius, b->color);
}

void bullet_move(Bullet b) {
  b->pos.x += cos(RADIANS(b->direction)) * b->speed;
  b->pos.y += sin(RADIANS(b->direction)) * b->speed;
}

static void bullet_for_each_void(List bs, ForEachFunc function) {
  for (int i = 0; i < bs->len; i++) {
    function((Bullet) list_get(bs, i));
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

bool bullet_in_screen(Bullet b, int screen_width, int screen_height) {
  return 0 <= b->pos.x && b->pos.x <= screen_width && 0 <= b->pos.y && b->pos.y <= screen_height;
}

void bullet_despawn_all_off_screen(List bs, int screen_width, int screen_height) {
  for (int i = bs->len - 1; i >= 0; i--) {
    Bullet b = (Bullet) list_get(bs, i);
    if (!bullet_in_screen(b, screen_width, screen_height)) {
      list_remove(bs, i);
      bullet_free(b);
      i--;
    }
  }
}

void bullet_free_all(List bs) {
  list_free(bs);
}
