#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "raylib.h"

//TODO:
// 1. include doxygen docu.

extern void display_exit_screen(void);

extern void display_debugging_stats(void);

extern void display_score(int score);

extern void display_victory(void);

extern void display_game_over(int score);

extern void display_help_ui(void);

extern void display_controls(void);

#endif

