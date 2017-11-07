#include "inc.h"

SDL_Window		*g_window;
SDL_Renderer 	*g_renderer;
TTF_Font		*g_font;

enum {MENU, INGAME, OPTIONS};

int	loop()
{
	char	mode;

	mode = MENU;
	while (1)
	{
		if (mode == MENU)
			display_menu();
		else if (mode == INGAME)
			display_game();
		else if (mode == OPTIONS)
			display_options();
	}
	return (1);
}
