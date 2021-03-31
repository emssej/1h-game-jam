#pragma once

#include "utilities.h"

#define PLAYER_RADIUS 40
#define SNAKE_RADIUS 20

typedef struct
GameState
{
  _Bool running;
  unsigned short window_width, window_height;

  /* Game stuff. */
  _Bool found_snake;
  long long score, player_x, player_y, snake_x, snake_y;
} GameState;

void GameState_initialize (GameState *state, unsigned short window_width,
									unsigned short window_height);
void GameState_update (GameState *state);
