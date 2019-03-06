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
	//exit_function();
}

static void scrool_fn(int value)
{
	printf("new value: %d\n", value);
	return ;
}

static void options_btn(int value)
{
	int w;
	int h;
	SDL_Surface *background;

	SDL_GetWindowSize(g_window, &w, &h);
	background = SDL_CreateRGBSurface(0, w / 2, h / 2, 32, RMASK, GMASK, BMASK, AMASK);
	SDL_FillRect(background, &(SDL_Rect){0, 0, background->w, background->h},
			SDL_MapRGB(background->format, 0, 255, 0));
	(void)value;
	t_menu_entry	menu[] = {
		(t_menu_entry){"Options", TITLE, 0, 0},
		(t_menu_entry){"SCROOL", SCROLL, 0, &scrool_fn},
		(t_menu_entry){"Fake button", BUTTON, 0, 0},
		(t_menu_entry){"Retour", BUTTON, 0, &menu_exit}
	};
	t_menu_settings settings = (t_menu_settings){
		background,
		&(SDL_Rect){w / 4, h / 4, w / 2, h / 2},
		//NULL,
		0,		// padding
		300,		// button_with
		100,		// button_height
		0,
		g_font	// font
	};
	display_menu(settings, menu, 4);


}

static void launch_selector(int value)
{
	char *path;
	(void)value;
	path = file_selector(NULL, (t_selector_settings){g_surface,
		(SDL_Rect){10, 10, g_surface->w - 20, g_surface->h - 20}, 5,
		SDL_MapRGB(g_surface->format, 77, 77, 77),
		SDL_MapRGB(g_surface->format, 255, 111, 0),
		SDL_MapRGB(g_surface->format, 30, 30, 30), (SDL_Color){0, 0, 0, 255}});
	if (path)
		free(path);
}

static void launch_main_menu()
{
	t_menu_entry	menu[] = {
		(t_menu_entry){"Super INNER", TITLE, 0, 0},
		(t_menu_entry){"Jouer!", BUTTON, 0, 0},
		(t_menu_entry){"SCROOL", SCROLL, 0, &scrool_fn},
		(t_menu_entry){"Option", BUTTON, 0, &options_btn},
		(t_menu_entry){"Selector", BUTTON, 4, &launch_selector},
		(t_menu_entry){"Quitter", BUTTON, 0, &menu_exit}
	};
	t_menu_settings settings = (t_menu_settings){
		NULL,	// background
		NULL,	// position
		0,		// padding
		300,		// button_with
		100,		// button_height
		0,
		g_font	// font
	};
	display_menu(settings, menu, 6);
}

int	loop()
{
	launch_main_menu();
	return (1);
}
