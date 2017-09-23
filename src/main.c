#include "inc.h"
#include "res.h"
#include "player.h"
#include "event.h"
#include <stdio.h>

SDL_Window		*g_window;
SDL_Renderer 	*g_renderer;
TTF_Font		*g_font;
t_key			*g_key;
int				g_fps;

static int  init_SDL(void)
{
	int imgflags;

  g_window = NULL;
  g_renderer = NULL;
  g_font = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return (0);
  g_window = SDL_CreateWindow("line", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);
  if (!g_window)
    return (0);
  g_renderer = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED );
  if (!g_renderer)
    return (0);
  SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if( TTF_Init() == -1 )
		return (0);
	g_font = TTF_OpenFont("res/DejaVuSansMono.ttf", 38);
	if(g_font == NULL)
		return (0);
	imgflags = IMG_INIT_PNG;
	if(!(IMG_Init(imgflags) & imgflags))
		return (0);
  return(1);
}

int   main(int argc, char **argv)
{
	t_player	*player;

  (void)argc;
  (void)argv;
	srand(time(NULL));
  if (!init_SDL())
  {
    write(2, "error during initialisation\n", 28);
    return (1);
  }
	player = init_player();
	if (!player)
	{
		write(2, "error during player initialisation\n", 35);
		return (1);
	}
	init_res();
	g_fps = 60;
	g_key = (t_key*)malloc(sizeof(t_key));
	g_key->right_button = 0;
  loop(player);
}
