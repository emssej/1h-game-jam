#include "graphics.h"

int
main ()
{
  GameState state = { 0 };
  GameState_initialize (&state, 640, 480);
  
  GraphicsContext gfx_ctx = { 0 };
  GraphicsContext_initialize (&gfx_ctx, &state);

  SDL_Event event;
  
  while (state.running)
	 {
		while (SDL_PollEvent (&event))
		  {
			 switch (event.type)
				{
				case SDL_QUIT:
				  {
					 state.running = 0;
				  }
				  break;
				case SDL_MOUSEMOTION:
				  {
					 state.player_x = event.motion.x;
					 state.player_y = event.motion.y;
				  }
				  break;
				case SDL_MOUSEBUTTONDOWN:
				  {
					 if (event.button.x > state.snake_x - SNAKE_RADIUS
						  && event.button.x < state.snake_x + SNAKE_RADIUS
						  && event.button.y > state.snake_y - SNAKE_RADIUS
						  && event.button.y < state.snake_y + SNAKE_RADIUS)
						{
						  state.found_snake = 1;
						}
				  }
				  break;
				default:
				  break;
				}
		  }

		GameState_update (&state);
		GraphicsContext_update (&gfx_ctx, &state);
	 }
  
  return 0;
}
