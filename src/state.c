#include "state.h"

void
GameState_initialize (GameState *state, unsigned short window_width,
							 unsigned short window_height)
{
  state->running = 1;
  state->window_width = window_width;
  state->window_height = window_height;

  state->found_snake = 1;
  state->score = -100;
  state->player_x = 0;
  state->player_y = 0;
  state->snake_x = 0;
  state->snake_y = 0;
}

void
GameState_update (GameState *state)
{
  if (state->found_snake)
	 {
		state->score = state->score + 100;
		state->snake_x = rand () % state->window_width;
		state->snake_y = rand () % state->window_height;

		state->found_snake = 0;

		INFO ("%Ld %Ld", state->snake_x, state->snake_y);
	 }
}
