#include "raylib.h"

#include "spaceship.h"

#define FPS 60


static void display_help_ui(void) {
  DrawText("Press Tab for Controls", 10, 10, 40, WHITE);
}

static void display_controls(void) {
  //remove magic numbers once merged with main
  DrawRectangle(10, 10, 800, 260, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(10, 10, 800, 260, BLUE);

  DrawText("Spaceship Controls:", 20, 20, 50, BLACK);
  DrawText("- Up Arrow to Accelerate", 40, 80, 50, BLACK);
  DrawText("- Right Arrow to Steer Right", 40, 140, 50, BLACK);
  DrawText("- Left Arrow to Steer Left", 40, 200, 50, BLACK);
}

int main(void) {
  // [Initialise Screen]
  InitWindow(0, 0, "Asteroids");
  ToggleFullscreen();
  int screen_width = GetScreenWidth();
  int screen_height = GetScreenHeight();
  SetTargetFPS(FPS);

  // [Initialise variables]
  Spaceship *spaceship = spaceship_initialise();

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

    if (IsKeyDown(KEY_TAB)) {
      display_controls();
    } else {
      display_help_ui();
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

    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Press F1 for Debugging Stats", 10, screen_height - 20, 20, WHITE);
    if (IsKeyDown(KEY_F1)) {
      DrawFPS(screen_width - 90, 10);
      DrawText(TextFormat("Screen Resolution: %d x %d", screen_width, screen_height), 10, 10, 20, LIME);
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

