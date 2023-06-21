#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "asteroids.h"
#include "bullet.h"
#include "collision.h"
#include "list.h"
#include "player.h"
#include "raylib.h"
#include "spaceship.h"

#define FPS                        60
#define NUM_BULLETS_PER_SECOND     20

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
#define SPACESHIP_SEPARATION       100

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

  DrawRectangle(
      0,
      QUARTER_SCREEN_HEIGHT_SIZE + MEDIUM_PADDING,
      SCREEN_WIDTH,
      EXTRA_LARGE_PADDING,
      Fade(BLUE, 0.5f)
    );

  DrawRectangleLines(
      0,
      QUARTER_SCREEN_HEIGHT_SIZE + MEDIUM_PADDING,
      SCREEN_WIDTH,
      EXTRA_LARGE_PADDING,
      RED
    );

  DrawText(
      exit_message,
      HALF_SCREEN_WIDTH_SIZE - exit_string_width / 2,
      HALF_SCREEN_HEIGHT_SIZE - LARGE_PADDING,
      LARGE_FONT_SIZE,
      WHITE
    );

  DrawText(
      save_message,
      HALF_SCREEN_WIDTH_SIZE - save_string_width / 2,
      HALF_SCREEN_HEIGHT_SIZE + SMALL_PADDING,
      MEDIUM_FONT_SIZE,
      WHITE
    );
}

static void display_debugging_stats(void) {
  const char *resolution_text = TextFormat("Screen Resolution: %d x %d", SCREEN_WIDTH, SCREEN_HEIGHT);

  int screen_res_string_width = MeasureText(resolution_text, EXTRA_SMALL_FONT_SIZE);

  DrawText(
      resolution_text,
      GetScreenWidth() - SMALL_PADDING - screen_res_string_width,
      SMALL_PADDING,
      EXTRA_SMALL_FONT_SIZE,
      LIME
    );

  DrawFPS(GetScreenWidth() - FPS_PADDING, SMALL_PADDING + SMALL_TEXT_HEIGHT);
}

static void display_help_ui(void) {
  DrawText("Press Tab for Controls", SMALL_PADDING, SMALL_PADDING, SMALL_FONT_SIZE, WHITE);
}

static void display_controls(void) {
  DrawRectangle(SMALL_PADDING, SMALL_PADDING, 875, 310, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(SMALL_PADDING, SMALL_PADDING, 875, 310, BLUE);

  DrawText("Spaceship Controls:", 20, 20, 50, BLACK);
  DrawText("- [UP ARROW] to Accelerate", 40, 80, 50, BLACK);
  DrawText("- [LEFT ARROW] to Steer Left", 40, 140, 50, BLACK);
  DrawText("- [RIGHT ARROW] to Steer Right", 40, 200, 50, BLACK);
  DrawText("- [SPACE] to Shoot", 40, 260, 50, BLACK);
}

int main(void) {
  // [Initialise screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  SetTargetFPS(FPS);

  // [Initialise audio]
  InitAudioDevice();
  Music music = LoadMusicStream("resources/bgm.mp3");
  Sound shoot_sound = LoadSound("resources/shoot.wav");
  PlayMusicStream(music);

  // [Initialise variables]
  List players = list_create(2, player_free);

  list_push(
      players,
      player_initialise(
        spaceship_initialise(
            HALF_SCREEN_WIDTH_SIZE - SPACESHIP_SEPARATION,
            HALF_SCREEN_HEIGHT_SIZE,
            RED
          ),
        bullet_init_all(),
        KEY_UP,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_DOWN,
        shoot_sound
      )
    );

  // if (multiplayer selected)
  list_push(
      players,
      player_initialise(
        spaceship_initialise(
            HALF_SCREEN_WIDTH_SIZE + SPACESHIP_SEPARATION,
            HALF_SCREEN_HEIGHT_SIZE,
            BLUE
          ),
        bullet_init_all(),
        KEY_W,
        KEY_A,
        KEY_D,
        KEY_S,
        shoot_sound
      )
    );

  List as = asteroids_create();

  int shoot_counter = 0;

  // [Initialise exit variables]
  SetExitKey(KEY_NULL);
  bool exit_window_requested = false;
  bool exit_window_drawn = false;
  bool exit_window = false;

  // [Drawing]
  while (!exit_window) {
    BeginDrawing();

    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) || list_length(as) == 0) {
      // freeze all entities
      exit_window_requested = true;
    }

    if (exit_window_requested) {
      if (!exit_window_drawn) {
        display_exit_screen();
        exit_window_drawn = true;
      }
      if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_ENTER)) {
        // save data here
        exit_window = true;
        exit_window_drawn = false;
      } else if (IsKeyPressed(KEY_N)) {
        exit_window_requested = false;
      }
      EndDrawing();
      continue;
    }

    ClearBackground(BLACK);
    UpdateMusicStream(music);

    shoot_counter = (shoot_counter + 1) % (int)ceil(1.0 * FPS / NUM_BULLETS_PER_SECOND);
    bool can_shoot = shoot_counter == 0;

    for (int i = 0; i < list_length(players); i++) {
      player_control(list_get(players, i), can_shoot);
    }

    DrawText(
        "Press F1 for Debugging Stats",
        SMALL_PADDING,
        GetScreenHeight() - MEDIUM_PADDING,
        SMALL_FONT_SIZE,
        WHITE
      );

    if (IsKeyDown(KEY_F1)) {
      display_debugging_stats();
    }

    asteroids_move(as);

    for (int i = 0; i < list_length(players); i++) {
      player_move(list_get(players, i));
    }

    for (int i = 0; i < list_length(players); i++) {
      bool player_lost = player_check_collision(list_get(players, i), as);
      exit_window_requested = exit_window_requested || player_lost;
    }

    asteroids_draw(as);

    for (int i = 0; i < list_length(players); i++) {
      player_draw(list_get(players, i));
    }

    if (IsKeyDown(KEY_TAB)) {
      display_controls();
    } else {
      display_help_ui();
    }

    EndDrawing();

    for (int i = 0; i < list_length(players); i++) {
      player_despawn_all_off_screen(list_get(players, i));
    }
  }

  // [Free]

  for (int i = 0; i < list_length(players); i++) {
    player_free(list_get(players, i));
  }
  asteroids_free(as);
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

