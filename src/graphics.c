#include "graphics.h"

void
GraphicsContext_initialize (GraphicsContext *ctx, GameState *state)
{
  ctx->window = SDL_CreateWindow ("Find the Snake", SDL_WINDOWPOS_UNDEFINED,
											 SDL_WINDOWPOS_UNDEFINED, state->window_width,
											 state->window_height, SDL_WINDOW_RESIZABLE
											 | SDL_WINDOW_ALLOW_HIGHDPI);

  if (!ctx->window)
	 {
		FATAL ("Could not initialize SDL window: %s", SDL_GetError ());
	 }

  ctx->renderer = SDL_CreateRenderer (ctx->window, -1,
												  SDL_RENDERER_ACCELERATED);

  if (!ctx->window)
	 {
		FATAL ("Could not initialize SDL renderer: %s", SDL_GetError ());
	 }

  ctx->screen = SDL_CreateTexture (ctx->renderer, SDL_PIXELFORMAT_ARGB8888,
											  SDL_TEXTUREACCESS_STREAMING,
											  state->window_width, state->window_height);

  void *pixels;
  int pitch;
  SDL_LockTexture (ctx->screen, NULL, &pixels, &pitch);
  
  cairo_surface_t *c = cairo_image_surface_create_for_data
	 (pixels, CAIRO_FORMAT_ARGB32, state->window_width, state->window_height,
	  pitch);

  ctx->canvas = cairo_create (c);

  SDL_UnlockTexture (ctx->screen);

  SDL_ShowCursor (0);
}

void
GraphicsContext_update (GraphicsContext *ctx, GameState *state)
{
  void *pixels;
  int pitch;
  SDL_LockTexture (ctx->screen, NULL, &pixels, &pitch);

  cairo_set_source_rgba (ctx->canvas, 0.1, 0.1, 0.1, 1.0);
  cairo_rectangle (ctx->canvas, 0, 0, state->window_width,
						 state->window_height);
  cairo_fill (ctx->canvas);

  /* Draw the player. */
  cairo_pattern_t *p = cairo_pattern_create_radial
	 (state->player_x, state->player_y, 0, state->player_x, state->player_y,
	  PLAYER_RADIUS);

  cairo_pattern_add_color_stop_rgba (p, 0, 0.9, 0.9, 0.9, 1.0);
  cairo_pattern_add_color_stop_rgba (p, 1, 0.9, 0.9, 0.9, 0.0);

  cairo_set_source (ctx->canvas, p);
  cairo_arc (ctx->canvas, state->player_x, state->player_y, PLAYER_RADIUS,
				 0, 2 * M_PI);
  cairo_fill (ctx->canvas);
  
  /* Draw the "snake". */
  
  cairo_set_source_rgba (ctx->canvas, 0.1, 0.9, 0.1, 1.0);
  cairo_set_line_width (ctx->canvas, 4);
  cairo_new_path (ctx->canvas);
  cairo_move_to (ctx->canvas, state->snake_x - SNAKE_RADIUS, state->snake_y
					  - SNAKE_RADIUS);
  cairo_curve_to (ctx->canvas, state->snake_x, state->snake_y - SNAKE_RADIUS,
						state->snake_x - SNAKE_RADIUS, state->snake_y + SNAKE_RADIUS,
						state->snake_x + SNAKE_RADIUS, state->snake_y + SNAKE_RADIUS);
  cairo_stroke (ctx->canvas);

  /* Draw the score. */
  char buf[512];
  sprintf (buf, "Score: %Ld", state->score);

  cairo_set_source_rgba (ctx->canvas, 0.9, 0.9, 0.9, 1.0);
  cairo_set_font_size (ctx->canvas, 14.0);
  cairo_move_to (ctx->canvas, 10, 20);
  cairo_show_text (ctx->canvas, buf);

  
   
  SDL_UnlockTexture (ctx->screen);
  SDL_RenderCopy (ctx->renderer, ctx->screen, NULL, NULL);
  SDL_RenderPresent(ctx->renderer);
}
