#include "highscore.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#define HIGHSCORE_FILE_NAME "highscore.data"

int get_highscore(void) {
  if (!FileExists(HIGHSCORE_FILE_NAME)) {
    SaveFileText(HIGHSCORE_FILE_NAME, "0");
  }

  int highscore = 0;
  char *buf;

  buf = LoadFileText(HIGHSCORE_FILE_NAME);
  if (buf == NULL) {
    return highscore;
  }

  highscore = atoi(buf);

  return highscore;
}

bool write_highscore(int score) {
  int highscore = get_highscore();
  char buf[MAXIMUM_SCORE_STRING_LENGTH];

  sprintf(buf, "%d", score);

  if (score >= highscore) {
    return SaveFileText(HIGHSCORE_FILE_NAME, buf);
  }

  return false;
}

