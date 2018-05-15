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
	char			mode;
	t_menu_entry	menu[] = {
	(t_menu_entry){"Jouer!", BUTTON, 0, 0},
	(t_menu_entry){"Option", BUTTON, 0, 0},
	(t_menu_entry){"Quitter", BUTTON, 0, 0}
	};

	mode = MENU;
	while (1)
	{
//		event(0, NULL);
		if (mode == MENU)
			display_menu(NULL, menu, 3);
		else if (mode == INGAME)
			display_game();
		else if (mode == OPTIONS)
			display_options();
		SDL_UpdateWindowSurface(g_window);	
	}
	return (1);
}
