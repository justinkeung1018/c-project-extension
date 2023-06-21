#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "raylib.h"

#define MAXIMUM_SCORE_STRING_LENGTH 3

//TODO
// 1. include doxygen documentation

extern int get_highscore(void);

extern bool write_highscore(int score);

#endif

