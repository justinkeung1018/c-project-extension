#include "raylib.h"
#include "loading.h"

#define FPS 60

int main(void) {
  // [Initialise Screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  int screen_width = GetScreenWidth();
  int screen_height = GetScreenHeight();
  SetTargetFPS(FPS);

  // [Setup Loading Screen]
  // int logoPositionX = screen_width/2 - 128;
  // int logoPositionY = screen_height/2 - 128;

//  int framesCounter = 0;
//  int lettersCount = 0;

 //  int topSideRecWidth = 16;
 //  int leftSideRecHeight = 16;

  // int bottomSideRecWidth = 16;
  // int rightSideRecHeight = 16;

  // int state = 0;                  // Tracking animation states (State Machine)
  // float alpha = 1.0f;             // Useful for fading

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

    BeginDrawing();

      ClearBackground(BLACK);
    //update_variables(state, framesCounter, topSideRecWidth, leftSideRecHeight, bottomSideRecWidth, rightSideRecHeight, lettersCount, alpha);
    //display_loading_animation(state, framesCounter, logoPositionX, logoPositionY, topSideRecWidth, leftSideRecHeight, rightSideRecHeight, bottomSideRecWidth, alpha, lettersCount);

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

