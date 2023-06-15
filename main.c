#include "raylib.h"

#include "spaceship.h"

#define FPS                   60

// Font sizes
#define LARGE_FONT_SIZE       100
#define MEDIUM_FONT_SIZE      80
#define SMALL_FONT_SIZE       40
#define EXTRA_SMALL_FONT_SIZE 20

static void display_exit_screen(void) {
  const char exit_message[] = "Are you sure you want to quit? [Y/N]";
  const char save_message[] = "(your current progress will not be saved)";

  int exit_string_width = MeasureText(exit_message, LARGE_FONT_SIZE);
  int save_string_width = MeasureText(save_message, MEDIUM_FONT_SIZE);

  DrawRectangle(0, GetScreenHeight() / 4 + 50, GetScreenWidth(), 1000, Fade(BLUE, 0.5f));
  DrawRectangleLines(0, GetScreenHeight() / 4 + 50, GetScreenWidth(), 1000, RED);
  DrawText(exit_message, GetScreenWidth() / 2 - exit_string_width / 2, GetScreenHeight() / 2 - 130, LARGE_FONT_SIZE, WHITE);
  DrawText(save_message, GetScreenWidth() / 2 - save_string_width / 2, GetScreenHeight() / 2 + 10, MEDIUM_FONT_SIZE, WHITE);
}

static void display_debugging_stats(void) {
  DrawFPS(GetScreenWidth() - 80, 10);
  DrawText(TextFormat("Screen Resolution: %d x %d", GetScreenWidth(), GetScreenHeight()), 10, 10, EXTRA_SMALL_FONT_SIZE, LIME);
}

int main(void) {
  // [Initialise screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  SetTargetFPS(FPS);

  // [Initialise variables]
  Spaceship *spaceship = spaceship_initialise();

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
    BeginDrawing();

    ClearBackground(BLACK);

    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
      // freeze all entities
      exit_window_requested = true;
    }

    if (exit_window_requested) {
      // save data here
      if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_ENTER)) {
        exit_window = true;
      } else if (IsKeyPressed(KEY_N)) {
        exit_window_requested = false;
      }
    }

    if (exit_window_requested) {
      display_exit_screen();
    }


    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) {
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

    DrawText("Press F1 for Debugging Stats", 10, GetScreenHeight() - 40, SMALL_FONT_SIZE, WHITE);
    if (IsKeyDown(KEY_F1)) {
      display_debugging_stats();
    }

    spaceship_draw(spaceship);

    EndDrawing();
  }

  // [Free]
  spaceship_free(spaceship);
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

