#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asteroid.h"
#include "bullet.h"
#include "collision.h"
#include "highscore.h"
#include "list.h"
#include "loading.h"
#include "player.h"
#include "raylib.h"
#include "spaceship.h"
#include "userinterface.h"

#define FPS                    60
#define NUM_BULLETS_PER_SECOND 20

int main(void) {
  // [Initialise screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  SetTargetFPS(FPS);

  // [Setup loading screen]
  Loader loader = loading_initialise();

  // [Initialise game mode selection variables]
  bool selected = false;
  int selection = 0;

  // [Initialise audio]
  InitAudioDevice();
  Music music = LoadMusicStream("resources/bgm.mp3");
  Sound shoot_sound = LoadSound("resources/shoot.wav");
  PlayMusicStream(music);

  // [Initialise variables]
  int shoot_counter = 0;
  bool game_over_requested = false;
  List as = asteroid_create_all();
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

  // [Initialise exit variables]
  SetExitKey(KEY_NULL);
  bool exit_window_requested = false;
  bool exit_window_drawn = false;
  bool exit_window = false;

  // [Initialise score]
  int score = 0;

  // [Loading screen]
  while (!loader->fully_loaded) {
    BeginDrawing();
    ClearBackground(BLACK);

    update_variables(loader);
    display_loading_animation(loader);
    EndDrawing();
  }

  // [Gamemode selection screen]
  while (!selected) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyPressed(KEY_LEFT)) {
      selection = 0;
    }

    if (IsKeyPressed(KEY_RIGHT)) {
      selection = 1;
    }

    if (IsKeyPressed(KEY_ENTER)) {
      selected = true;
    }

    display_and_select_gamemode(selection);
    EndDrawing();
  }

  if (selection == 1) {
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
  }

  // [Drawing]
  while (!exit_window) {
    BeginDrawing();

    display_score(score);

    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
      exit_window_requested = true;
    }

    if (list_length(as) == 0) {
      display_victory();
      if (IsKeyPressed(KEY_ENTER)) {
        write_highscore(score);
        exit_window = true;
      }
    }

    if (exit_window_requested && !game_over_requested && list_length(as) != 0) {
      if (!exit_window_drawn) {
        display_exit_screen();
        exit_window_drawn = true;
      }
      if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_ENTER)) {
        exit_window = true;
        exit_window_drawn = false;
      } else if (IsKeyPressed(KEY_N)) {
        exit_window_drawn = false;
        exit_window_requested = false;
      }
      EndDrawing();
      continue;
    }

    if (game_over_requested) {
      if (IsKeyDown(KEY_ENTER)) {
        write_highscore(score);
        exit_window = true;
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

    asteroid_move_all(as);

    for (int i = 0; i < list_length(players); i++) {
      player_move(list_get(players, i));
    }

    for (int i = 0; i < list_length(players); i++) {
      bool player_lost = player_check_collision(list_get(players, i), as, &score);
      if (player_lost) {
        game_over_requested = true;
        display_game_over(score);
      }
    }

    asteroid_draw_all(as);

    for (int i = 0; i < list_length(players); i++) {
      player_draw(list_get(players, i));
    }

    if (IsKeyDown(KEY_TAB)) {
      display_controls();
    } else {
      display_help_ui();
    }

    for (int i = 0; i < list_length(players); i++) {
      player_despawn_all_off_screen(list_get(players, i));
    }

    EndDrawing();
  }

  // [Free]
  for (int i = 0; i < list_length(players); i++) {
    player_free(list_get(players, i));
  }
  loader_free(loader);
  asteroid_free_all(as);
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

