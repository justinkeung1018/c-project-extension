#include "raylib.h"

#define FPS 60
#define MAXIMUM_STRING_LENGTH 100

static void draw_exit_screen(void) {
  char exit_message[MAXIMUM_STRING_LENGTH] = "Are you sure you want to quit? [Y/N]";
  char save_message[MAXIMUM_STRING_LENGTH] = "(your current progress will not be saved)";

  int exit_string_length = MeasureText(exit_message, 100);
  int save_string_length = MeasureText(save_message, 80);

  DrawText(exit_message, GetScreenWidth() / 2 - exit_string_length / 2, GetScreenHeight() / 2 - 130, 100, WHITE);
  DrawText(save_message, GetScreenWidth() / 2 - save_string_length / 2, GetScreenHeight() / 2 + 10, 80, WHITE);
}

static void draw_debugging_tools(void) {
  DrawFPS(GetScreenWidth() - 80, 10);
  DrawText(TextFormat("Screen Resolution: %d x %d", GetScreenWidth(), GetScreenHeight()), 10, 10, 20, LIME);
}

int main(void) {
  // [Initialise Screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  SetTargetFPS(FPS);

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

    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) {
      PlaySound(sound); // combine this with other components
    }

    BeginDrawing();

    ClearBackground(BLACK);

    if (exit_window_requested) {
      draw_exit_screen();
    }

    DrawText("Press F1 for Debugging Stats", 10, GetScreenHeight() - 40, 40, WHITE);
    if (IsKeyDown(KEY_F1)) {
      draw_debugging_tools();
    }

    EndDrawing();
  }

  // [Free]
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

