#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "raylib.h"

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
#define SPACESHIP_SEPARATION       100

// Various screen sizes
#define SCREEN_WIDTH               GetScreenWidth()
#define SCREEN_HEIGHT              GetScreenHeight()
#define HALF_SCREEN_WIDTH_SIZE     GetScreenWidth() / 2
#define HALF_SCREEN_HEIGHT_SIZE    GetScreenHeight() / 2
#define QUARTER_SCREEN_HEIGHT_SIZE GetScreenHeight() / 4

// Score constants
#define SCORE_BUFFER_SIZE          100

/*
 * Displays the screen for the user to select Singleplayer or Multiplayer.
 * Draws an underscore on the option currently selected by the user.
 *
 * @param selection 0 for Singleplayer and 1 for Multiplayer.
 */
extern void display_and_select_gamemode(int selection);


/*
 * Displays the exit screen user interface.
 */
extern void display_exit_screen(void);

/*
 * Displays the debugging statistics (FPS and screen resolution).
 */
extern void display_debugging_stats(void);

/*
 * Displays the user's current score on the top of the screen.
 *
 * @param score The user's current score.
 */
extern void display_score(int score);

/*
 * Displays the victory screen.
 */
extern void display_victory(void);

/*
 * Displays the game over screen which includes the highscore.
 *
 * @param score The user's score for the session.
 */
extern void display_game_over(int score);

/*
 * Displays "Press TAB for user controls" on the top left screen.
 */
extern void display_help_ui(void);

/*
 * Displays the controls screen for the user.
 */
extern void display_controls(void);

#endif

