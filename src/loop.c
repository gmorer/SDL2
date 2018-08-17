#include "../inc/inc.h"
#include "../inc/menu.h"
#include "../inc/file_selector.h"

SDL_Window		*g_window;
SDL_Surface 	*g_surface;
TTF_Font		*g_font;

enum {MENU, INGAME, OPTIONS};

/*
 *	/!\ you ave to use the event() function on time by loop /!\
 *			default: event(0, NULL);
 */

static void	menu_exit(int value)
{
	(void)value;
	exit_function();
}

static void scrool_fn(int value)
{
	printf("new value: %d\n", value);
	return ;
}

static void launch_selector(int value)
{
	(void)value;
	file_selector(NULL, (t_selector_settings){g_surface,
		(SDL_Rect){10, 10, g_surface->w - 20, g_surface->h - 20}, 5,
		SDL_MapRGB(g_surface->format, 77, 77, 77),
		SDL_MapRGB(g_surface->format, 255, 111, 0), (SDL_Color){0, 0, 0, 255}});
}

int	loop()
{
	char			mode;
	t_menu_entry	menu[] = {
	(t_menu_entry){"Super INNER", TITLE, 0, 0},
	(t_menu_entry){"Jouer!", BUTTON, 0, 0},
	(t_menu_entry){"SCROOL", SCROLL, 0, &scrool_fn},
	(t_menu_entry){"Option", BUTTON, 0, 0},
	(t_menu_entry){"Selector", BUTTON, 4, &launch_selector},
	(t_menu_entry){"Quitter", BUTTON, 4, &menu_exit}
	};

	mode = MENU;
	while (1)
	{
//		event(0, NULL);
		if (mode == MENU)
			//display_menu(NULL, &(SDL_Rect){0, 0, SCREEN_X / 2, SCREEN_Y / 2}, g_font, menu, 5);
			display_menu(NULL, NULL, g_font, menu, 6);
		else if (mode == INGAME)
			display_game();
		else if (mode == OPTIONS)
			display_options();
		SDL_UpdateWindowSurface(g_window);	
	}
	return (1);
}
