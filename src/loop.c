#include "inc.h"

SDL_Window		*g_window;
SDL_Surface 	*g_surface;
TTF_Font		*g_font;

enum {MENU, INGAME, OPTIONS};

int	loop()
{
	char	mode;

	mode = MENU;
	while (1)
	{
		event();
		if (mode == MENU)
			display_menu();
		else if (mode == INGAME)
			display_game();
		else if (mode == OPTIONS)
			display_options();
		SDL_UpdateWindowSurface(g_window);	
	}
	return (1);
}
