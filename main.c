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
#include "raylib.h"
#include "spaceship.h"

#define FPS                        60
#define NUM_BULLETS_PER_SECOND     20

// Font sizes
#define EXTRA_SMALL_FONT_SIZE      20
#define SMALL_FONT_SIZE            40
#define MEDIUM_FONT_SIZE           80
#define LARGE_FONT_SIZE            100
#define EXTRA_LARGE_FONT_SIZE      200

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

// Score constants
#define SCORE_BUFFER_SIZE          100

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

static void display_score(int score) {
  char curr_score[SCORE_BUFFER_SIZE] = "Score: ";

  char score_str[MAXIMUM_SCORE_STRING_LENGTH + 1];
  sprintf(score_str, "%d", score);

  strcat(curr_score, score_str);

  int curr_score_text_width = MeasureText(curr_score, SMALL_FONT_SIZE);

  DrawText(
      curr_score,
      HALF_SCREEN_WIDTH_SIZE - curr_score_text_width / 2,
      SMALL_PADDING,
      SMALL_FONT_SIZE,
      GOLD
    );
}

static void display_victory(void) {
  int victory_text_width = MeasureText("Victory!", EXTRA_LARGE_FONT_SIZE);
  int exit_instruction_text_width = MeasureText("Press ENTER to Exit", LARGE_FONT_SIZE);

  DrawText(
      "Victory!",
      HALF_SCREEN_WIDTH_SIZE - victory_text_width / 2,
      HALF_SCREEN_HEIGHT_SIZE - LARGE_PADDING * 2,
      EXTRA_LARGE_FONT_SIZE,
      GOLD
    );

  DrawText(
      "Press ENTER to Exit",
      HALF_SCREEN_WIDTH_SIZE - exit_instruction_text_width / 2,
      HALF_SCREEN_HEIGHT_SIZE + LARGE_PADDING,
      LARGE_FONT_SIZE,
      GOLD
    );
}

static void display_game_over(int score) {
  int highscore = get_highscore();
  char highscore_str[MAXIMUM_SCORE_STRING_LENGTH + 1];
  sprintf(highscore_str, "%d", highscore);

  char curr_highscore[] = "Current Highscore: ";
  strcat(curr_highscore, highscore_str);

  int game_over_text_width = MeasureText("Game Over!", EXTRA_LARGE_FONT_SIZE);
  int exit_instruction_text_width = MeasureText("Press ENTER to Exit", LARGE_FONT_SIZE);
  int highscore_text_width = MeasureText(curr_highscore, MEDIUM_FONT_SIZE);
  int new_highscore_text_width_1 = MeasureText("Congratulations!", SMALL_FONT_SIZE);
  int new_highscore_text_width_2 = MeasureText("new highscore detected", SMALL_FONT_SIZE);

  DrawText(
      "Game Over!",
      HALF_SCREEN_WIDTH_SIZE - game_over_text_width / 2,
      HALF_SCREEN_HEIGHT_SIZE - LARGE_PADDING * 2,
      EXTRA_LARGE_FONT_SIZE,
      RED
    );

  DrawText(
      curr_highscore,
      HALF_SCREEN_WIDTH_SIZE - highscore_text_width / 2,
      HALF_SCREEN_HEIGHT_SIZE + LARGE_PADDING * 4,
      MEDIUM_FONT_SIZE,
      LIME
    );

  if (score > highscore) {
    DrawText(
        "Congratulations!",
        HALF_SCREEN_WIDTH_SIZE - new_highscore_text_width_1 / 2,
        HALF_SCREEN_HEIGHT_SIZE + LARGE_PADDING * 6,
        SMALL_FONT_SIZE,
        LIME
      );

    DrawText(
        "new highscore detected",
        HALF_SCREEN_WIDTH_SIZE - new_highscore_text_width_2 / 2,
        HALF_SCREEN_HEIGHT_SIZE + LARGE_PADDING * 6 + SMALL_PADDING * 4,
        SMALL_FONT_SIZE,
        LIME
      );
  }

  DrawText(
      "Press ENTER to Exit",
      HALF_SCREEN_WIDTH_SIZE - exit_instruction_text_width / 2,
      HALF_SCREEN_HEIGHT_SIZE,
      LARGE_FONT_SIZE,
      RED
    );
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

  // [Setup loading screen]
  Loader loader = loading_initialise();

  // [Initialise variables]
  Spaceship spaceship = spaceship_initialise();
  List as = asteroid_create_all();
  List bullets = bullet_init_all();
  int can_shoot = 0;

  bool game_over_requested = false;

  // [Initialise audio]
  InitAudioDevice();
  Music music = LoadMusicStream("resources/bgm.mp3");
  Sound sound = LoadSound("resources/shoot.wav");
  // to implement explosion when we combine other files
  PlayMusicStream(music);

  // [Initialise exit variables]
  SetExitKey(KEY_NULL);
  bool exit_window_requested = false;
  bool exit_window_drawn = false;
  bool exit_window = false;

  // [Initialise score]
  int score = 0;

  while (!loader->fully_loaded) {
    BeginDrawing();
    ClearBackground(BLACK);

    update_variables(loader);
    display_loading_animation(loader);
    EndDrawing();
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
      write_highscore(score);
      if (IsKeyPressed(KEY_ENTER)) {
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
        exit_window = true;
      }
      EndDrawing();
      continue;
    }

    ClearBackground(BLACK);
    UpdateMusicStream(music);
    can_shoot = (can_shoot + 1) % (int)ceil(1.0 * FPS / NUM_BULLETS_PER_SECOND);

    if (IsKeyDown(KEY_SPACE) && can_shoot == 0) {
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
    bullet_move_all(bullets);
    spaceship_move(spaceship);

    for (int i = 0; i < list_length(as); i++) {
      Asteroid a = list_get(as, i);
      if (collides_asteroid_spaceship(a, spaceship)) {
        game_over_requested = true;
        display_game_over(score);
        write_highscore(score);
      }
      bool asteroid_broken = false;
      for (int j = 0; j < list_length(bullets); j++) {
        Bullet b = list_get(bullets, j);
        if (collides_asteroid_bullet(a, b)) {
          if (!asteroid_broken) {
            // Handle edge case where multiple bullets collide with the same asteroid
            // to avoid breaking the same asteroid more than once
            score++;
            asteroid_break(as, i);
            asteroid_broken = true;
          }
          list_remove(bullets, j);
          bullet_free(b);
        }
      }
    }

    asteroid_draw_all(as);
    bullet_draw_all(bullets);
    spaceship_draw(spaceship);

    if (IsKeyDown(KEY_TAB)) {
      display_controls();
    } else {
      display_help_ui();
    }

    bullet_despawn_all_off_screen(bullets);

    EndDrawing();
  }

  // [Free]
  loader_free(loader);
  spaceship_free(spaceship);
  bullet_free_all(bullets);
  asteroid_free_all(as);
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

