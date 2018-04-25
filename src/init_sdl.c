#include "inc.h"

SDL_Window		*g_window;
SDL_Renderer 	*g_renderer;
TTF_Font		*g_font;

static int	print_error()
{
	fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
	return (0);
}

static int	print_ttf_error()
{
	fprintf(stderr, "SDL_Init failed: %s\n", TTF_GetError());
	return (0);
}

int		init_sdl()
{
	g_window = NULL;
	g_surface = NULL;
	g_font = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (print_error());
	g_window = SDL_CreateWindow("line", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);
	if (!g_window)
		return (print_error());
		g_surface = SDL_GetWindowSurface(g_window);
	if (!g_surface)
		return (print_error());
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if( TTF_Init() == -1 )
		return (print_ttf_error());
	g_font = TTF_OpenFont("res/DejaVuSansMono.ttf", 38);
	if(g_font == NULL)
		return (print_ttf_error());
	return (1);
}
