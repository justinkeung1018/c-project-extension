#include "userinterface.h"

#include <stdio.h>
#include <string.h>

#include "highscore.h"
#include "raylib.h"

void display_and_select_gamemode(int selection) {
  int select_gamemode_string_width = MeasureText("Select Gamemode", EXTRA_LARGE_FONT_SIZE);
  int singleplayer_string_width = MeasureText("Singleplayer", LARGE_FONT_SIZE);
  int multiplayer_string_width = MeasureText("Multiplayer", LARGE_FONT_SIZE);
  int confirmation_string_width = MeasureText("Press ENTER to Confirm", SMALL_FONT_SIZE);

  int singleplayer_string_x = HALF_SCREEN_WIDTH_SIZE - singleplayer_string_width - LARGE_PADDING;
  int multiplayer_string_x = HALF_SCREEN_WIDTH_SIZE + LARGE_PADDING;
  int selection_string_y = HALF_SCREEN_HEIGHT_SIZE;

  DrawText(
      "Select Gamemode",
      HALF_SCREEN_WIDTH_SIZE - select_gamemode_string_width / 2,
      HALF_SCREEN_HEIGHT_SIZE - LARGE_PADDING * 5,
      EXTRA_LARGE_FONT_SIZE,
      WHITE
    );

  DrawText(
      "Singleplayer",
      singleplayer_string_x,
      selection_string_y,
      LARGE_FONT_SIZE,
      WHITE
    );

  DrawText(
      "Multiplayer",
      multiplayer_string_x,
      selection_string_y,
      LARGE_FONT_SIZE,
      WHITE
    );

  DrawRectangle(
      (selection == 0 ? singleplayer_string_x : multiplayer_string_x),
      selection_string_y + LARGE_PADDING + SMALL_PADDING * 2,
      (selection == 0 ? singleplayer_string_width : multiplayer_string_width),
      10,
      WHITE
    );

  DrawText(
      "Press ENTER to Confirm",
      HALF_SCREEN_WIDTH_SIZE - confirmation_string_width / 2,
      HALF_SCREEN_HEIGHT_SIZE + QUARTER_SCREEN_HEIGHT_SIZE / 2,
      SMALL_FONT_SIZE,
      PURPLE
    );
}

void display_exit_screen(void) {
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

void display_debugging_stats(void) {
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

void display_score(int score) {
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

void display_victory(void) {
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

void display_game_over(int score) {
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

void display_help_ui(void) {
  DrawText("Press Tab for Controls", SMALL_PADDING, SMALL_PADDING, SMALL_FONT_SIZE, WHITE);
}

void display_controls(void) {
  DrawRectangle(SMALL_PADDING, SMALL_PADDING, 875, 310, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(SMALL_PADDING, SMALL_PADDING, 875, 310, BLUE);

  DrawText("Spaceship Controls:", 20, 20, 50, BLACK);
  DrawText("- [UP ARROW] to Accelerate", 40, 80, 50, BLACK);
  DrawText("- [LEFT ARROW] to Steer Left", 40, 140, 50, BLACK);
  DrawText("- [RIGHT ARROW] to Steer Right", 40, 200, 50, BLACK);
  DrawText("- [SPACE] to Shoot", 40, 260, 50, BLACK);
}

