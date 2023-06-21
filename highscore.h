#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "raylib.h"

#define MAXIMUM_SCORE_STRING_LENGTH 3

/*
 * Gets the highscore from highscore.data file.
 *
 * @return The highscore.
 */
extern int get_highscore(void);

/*
 * Updates the player's highscore.
 *
 * @return True if new highscore is written, otherwise false.
 */
extern bool write_highscore(int score);

#endif

