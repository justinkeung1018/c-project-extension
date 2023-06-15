#include "raylib.h"

#include "spaceship.h"

#define FPS                   60

#define MAXIMUM_STRING_LENGTH 100

// Font Sizes
#define LARGE_FONT_SIZE       100
#define MEDIUM_FONT_SIZE      80
#define SMALL_FONT_SIZE       40
#define EXTRA_SMALL_FONT_SIZE 20

static void draw_exit_screen(void) {
  char exit_message[MAXIMUM_STRING_LENGTH] = "Are you sure you want to quit? [Y/N]";
  char save_message[MAXIMUM_STRING_LENGTH] = "(your current progress will not be saved)";

  int exit_string_length = MeasureText(exit_message, LARGE_FONT_SIZE);
  int save_string_length = MeasureText(save_message, MEDIUM_FONT_SIZE);

  DrawText(exit_message, GetScreenWidth() / 2 - exit_string_length / 2, GetScreenHeight() / 2 - 130, LARGE_FONT_SIZE, WHITE);
  DrawText(save_message, GetScreenWidth() / 2 - save_string_length / 2, GetScreenHeight() / 2 + 10, MEDIUM_FONT_SIZE, WHITE);
}

static void draw_debugging_tools(void) {
  DrawFPS(GetScreenWidth() - 80, 10);
  DrawText(TextFormat("Screen Resolution: %d x %d", GetScreenWidth(), GetScreenHeight()), 10, 10, EXTRA_SMALL_FONT_SIZE, LIME);
}

int main(void) {
  // [Initialise Screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  SetTargetFPS(FPS);

  // [Initialise variables]
  Spaceship *spaceship = spaceship_initialise();

  // [Initialise Audio]
  InitAudioDevice();
  Music music = LoadMusicStream("resources/bgm.mp3");
  Sound sound = LoadSound("resources/shoot.wav");
  // to implement explosion when we combine other files

  PlayMusicStream(music);

  // [Initialise Exit]
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
      draw_exit_screen();
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
      draw_debugging_tools();
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

