#include "raylib.h"

#define FPS 60

static void display_controls(void) {
  // draw text
}

int main(void) {
  // [Initialise Screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  int screen_width = GetScreenWidth();
  int screen_height = GetScreenHeight();
  SetTargetFPS(FPS);

  // [Initialise Audio]
  InitAudioDevice();
  Music music = LoadMusicStream("resources/bgm.mp3");
  Sound sound = LoadSound("resources/shoot.wav");
  // to implement explosion when we combine other files

  PlayMusicStream(music);

  // [Drawing]
  while (!WindowShouldClose()) {
    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) {
      PlaySound(sound); // combine this with other components
    }

    if (IsKeyPressed(KEY_TAB)) {
      // display controls
    }

    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Press F1 for Debugging Stats", 10, screen_height - 20, 20, WHITE);
    if (IsKeyDown(KEY_F1)) {
      DrawFPS(screen_width - 90, 10);
      DrawText(TextFormat("Screen Resolution: %d x %d", screen_width, screen_height), 10, 10, 20, LIME);
    }

    EndDrawing();
  }

  // [Free]
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

