#include <stdbool.h>
#include <stdlib.h>

#include "asteroids.h"
#include "bullet.h"
#include "collision.h"
#include "list.h"
#include "raylib.h"
#include "spaceship.h"

#define FPS                        60

// Font sizes
#define LARGE_FONT_SIZE            100
#define MEDIUM_FONT_SIZE           80
#define SMALL_FONT_SIZE            40
#define EXTRA_SMALL_FONT_SIZE      20

// Text height
#define SMALL_TEXT_HEIGHT          20

// Padding
#define SMALL_PADDING              10
#define MEDIUM_PADDING             50
#define LARGE_PADDING              100
#define EXTRA_LARGE_PADDING        1000
#define FPS_PADDING                80

// Various screen sizes
#define SCREEN_WIDTH               GetScreenWidth()
#define SCREEN_HEIGHT              GetScreenHeight()
#define HALF_SCREEN_WIDTH_SIZE     GetScreenWidth() / 2
#define HALF_SCREEN_HEIGHT_SIZE    GetScreenHeight() / 2
#define QUARTER_SCREEN_HEIGHT_SIZE GetScreenHeight() / 4

static void display_exit_screen(void) {
  const char exit_message[] = "Are you sure you want to quit? [Y/N]";
  const char save_message[] = "(your current progress will not be saved)";

  int exit_string_width = MeasureText(exit_message, LARGE_FONT_SIZE);
  int save_string_width = MeasureText(save_message, MEDIUM_FONT_SIZE);

  DrawRectangle(0, QUARTER_SCREEN_HEIGHT_SIZE + MEDIUM_PADDING, SCREEN_WIDTH, EXTRA_LARGE_PADDING, Fade(BLUE, 0.5f));
  DrawRectangleLines(0, QUARTER_SCREEN_HEIGHT_SIZE + MEDIUM_PADDING, SCREEN_WIDTH, EXTRA_LARGE_PADDING, RED);
  DrawText(exit_message, HALF_SCREEN_WIDTH_SIZE - exit_string_width / 2, HALF_SCREEN_HEIGHT_SIZE - LARGE_PADDING, LARGE_FONT_SIZE, WHITE);
  DrawText(save_message, HALF_SCREEN_WIDTH_SIZE - save_string_width / 2, HALF_SCREEN_HEIGHT_SIZE + SMALL_PADDING, MEDIUM_FONT_SIZE, WHITE);
}

static void display_debugging_stats(void) {
  const char *resolution_text = TextFormat("Screen Resolution: %d x %d", SCREEN_WIDTH, SCREEN_HEIGHT);

  int screen_res_string_width = MeasureText(resolution_text, EXTRA_SMALL_FONT_SIZE);

  DrawText(resolution_text, GetScreenWidth() - SMALL_PADDING - screen_res_string_width, SMALL_PADDING, EXTRA_SMALL_FONT_SIZE, LIME);
  DrawFPS(GetScreenWidth() - FPS_PADDING, SMALL_PADDING + SMALL_TEXT_HEIGHT);
}

int main(void) {
  // [Initialise screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  SetTargetFPS(FPS);

  // [Initialise variables]
  Spaceship spaceship = spaceship_initialise();
  List as = asteroids_create();
  List bullets = bullet_init_all();
  bool breakable;

  // [Initialise audio]
  InitAudioDevice();
  Music music = LoadMusicStream("resources/bgm.mp3");
  Sound sound = LoadSound("resources/shoot.wav");
  // to implement explosion when we combine other files
  PlayMusicStream(music);

  // [Initialise exit variables]
  SetExitKey(KEY_NULL);
  bool exit_window_requested = false;
  bool exit_window = false;

  // [Drawing]
  while (!exit_window) {
    breakable = true;

    BeginDrawing();

    if (!exit_window_requested && (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))) {
      // freeze all entities
      exit_window_requested = true;
      display_exit_screen();
    }

    if (exit_window_requested) {
      if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_ENTER)) {
      	// save data here
        exit_window = true;
      } else if (IsKeyPressed(KEY_N)) {
        exit_window_requested = false;
      }
      EndDrawing();
      continue;
    }

    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) {
      spaceship_shoot(spaceship, bullets);
      PlaySound(sound); // combine this with other components
    }

    if (IsKeyDown(KEY_UP)) {
      spaceship_accelerate(spaceship);
    } else {
      spaceship_reset_acceleration(spaceship);
    }

    if (IsKeyDown(KEY_LEFT)) {
      spaceship_rotate_left(spaceship);
    }

    if (IsKeyDown(KEY_RIGHT)) {
      spaceship_rotate_right(spaceship);
    }

    if (IsKeyPressed(KEY_ENTER) && breakable && !list_empty(as)) {
      asteroid_break(as, 0);
      breakable = false;
    }

    DrawText("Press F1 for Debugging Stats", SMALL_PADDING, GetScreenHeight() - MEDIUM_PADDING, SMALL_FONT_SIZE, WHITE);
    if (IsKeyDown(KEY_F1)) {
      display_debugging_stats();
    }

    asteroids_move(as);
    bullet_move_all(bullets);
    spaceship_move(spaceship);

    for (int i = 0; i < list_length(as); i++) {
      Asteroid a = list_get(as, i);
      if (collides_asteroid_spaceship(a, spaceship)) {
        exit_window_requested = true;
      }
    }

    asteroids_draw(as);
    bullet_draw_all(bullets);
    spaceship_draw(spaceship);

    EndDrawing();

    bullet_despawn_all_off_screen(bullets);
  }

  // [Free]
  spaceship_free(spaceship);
  bullet_free_all(bullets);
  asteroids_free(as);
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

