#include "inc.h"
#include "menu.h"

SDL_Surface	*g_surface;


/*	the menu take : a background type: SDL_Surface
 *  and an array of object t_menu_entry
 *  {
 *    name: char*,
 *    value: char,
 *    function: (*f)(char c)
 *   }
 *  the array terminate with a NULL
 */

void	draw(void)
{
	/* background */
	SDL_FillRect(g_surface, NULL, SDL_MapRGB(g_surface->format,
	0, 0, 255));
	SDL_FillRect(g_surface, &(SDL_Rect){SCREEN_X / 2 - 100,
	SCREEN_Y / 4, 200, 50}, SDL_MapRGB(g_surface->format,
	100, 100, 0));
	SDL_FillRect(g_surface, &(SDL_Rect){SCREEN_X / 2 - 100, 
	SCREEN_Y / 2 + SCREEN_Y / 4 - 50, 200, 50},
	SDL_MapRGB(g_surface->format, 100, 100, 0));
	SDL_FillRect(g_surface, &(SDL_Rect){SCREEN_X / 2 - 100,
	SCREEN_Y / 2 - 25, 200, 50}, SDL_MapRGB(g_surface->format,
	100, 100, 0));
}

void	display_menu(SDL_Surface *background, t_menu_entry *entry)
{
	static int index = 0;

	draw();
	if (!background || !entry)
	{
		index = 0;
		return;
	}
}
