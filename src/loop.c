#include "inc.h"
#include "menu.h"

SDL_Window		*g_window;
SDL_Surface 	*g_surface;
TTF_Font		*g_font;

enum {MENU, INGAME, OPTIONS};

/*
 *	/!\ you ave to use the event() function on time by loop /!\
 *			default: event(0, NULL);
 */

int	loop()
{
	char	mode;

	mode = MENU;
	while (1)
	{
//		event(0, NULL);
		if (mode == MENU)
			display_menu(NULL, NULL, 4);
		else if (mode == INGAME)
			display_game();
		else if (mode == OPTIONS)
			display_options();
		SDL_UpdateWindowSurface(g_window);	
	}
	return (1);
}
