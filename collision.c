#include "collision.h"

#include "asteroids.h"
#include "bullet.h"
#include "spaceship.h"
#include "raymath.h"

static Vector2 project(Vector2 vector, Vector2 onto) {
  float scale = Vector2DotProduct(vector, onto) / Vector2LengthSqr(onto);
  return Vector2Scale(onto, scale);
}

bool collides_asteroid_spaceship(Asteroid a, Spaceship s) {
  int length = s->collider.length;

  // Check if any vertex of the spaceship is inside the asteroid
  for (int i = 0; i < length; i++) {
    if (CheckCollisionPointCircle(s->collider.vectors[i], a->position, a->size)) {
      return true;
    }
  }

  // Check if the centre of the asteroid is inside the spaceship
  bool centre_in_spaceship = true;
  for (int i = 0; i < length; i++) {
    Vector2 v1 = s->collider.vectors[i];
    Vector2 v2 = s->collider.vectors[(i + 1) % length];
    Vector2 edge = Vector2Subtract(v2, v1);
    Vector2 normal = Vector2Rotate(edge, M_PI / 2);

    Vector2 v1_to_centre = Vector2Subtract(a->position, v1);

    float dot_product = Vector2DotProduct(normal, v1_to_centre);
    centre_in_spaceship = centre_in_spaceship && (dot_product > 0);
  }

  if (centre_in_spaceship) {
    return true;
  }

  // Check if any edge of the spaceship intersects the asteroid
  for (int i = 0; i < length; i++) {
    Vector2 v1 = s->collider.vectors[i];
    Vector2 v2 = s->collider.vectors[(i + 1) % length];
    Vector2 edge = Vector2Subtract(v2, v1);
    Vector2 v1_to_centre = Vector2Subtract(a->position, v1);

    if (Vector2DotProduct(v1_to_centre, edge) < 0) {
      // The circle is beyond the line
      continue;
    }

    Vector2 projection = project(v1_to_centre, edge);
    Vector2 normal = Vector2Subtract(v1_to_centre, projection);
    if (Vector2LengthSqr(normal) <= a->size * a->size) {
      return true;
    }
  }

  return false;
}

bool collides_asteroid_bullet(Asteroid a, Bullet b) {
  return CheckCollisionPointCircle(b->position, a->position, a->size);
}

