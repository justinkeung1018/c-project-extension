#include "raylib.h"

#define FPS           240

int main(void) {

  // [Initialise]
  InitWindow(0, 0, "Asteroids");  
  ToggleFullscreen();
  int screen_width = GetScreenWidth();
  int screen_height = GetScreenHeight();

  SetTargetFPS(FPS);

  InitAudioDevice();

  Music music = LoadMusicStream("resources/bgm.mp3");
  Sound sound = LoadSound("resources/ring.wav");

  PlayMusicStream(music);

  // [Drawing]
  while (!WindowShouldClose()) {
    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) PlaySound(sound);
    
    BeginDrawing();

      ClearBackground(BLACK);
      DrawFPS(screen_width - 90, 10);
      DrawText(TextFormat("Screen resolution: %ix%i", screen_width, screen_height), 10, 10, 20, DARKBLUE);

    EndDrawing();
  }

  // [Free]
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

