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

static SDL_Surface	*default_background(void)
{
	unsigned int	rmask;
	unsigned int	gmask;
	unsigned int	bmask;
	unsigned int	amask;
	SDL_Surface		*result;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
	result = SDL_CreateRGBSurface(
		0,
		SCREEN_X,
		SCREEN_Y,
		32,
		rmask,
		gmask,
		bmask,
		amask
	);
	SDL_FillRect(result,
		&(SDL_Rect){0, 0, SCREEN_X, SCREEN_Y},
		SDL_MapRGB(result->format, 0, 0, 255)
	);
	return (result);
}

static void	draw_buttons(t_menu_entry *entry, char len, char selected_index)
{
	char	index;
	int		space_between;
	int		y;
	int		button_y;

	(void)selected_index;
	button_y = 50;
	index = 0;
	space_between = (SCREEN_Y - button_y * len + 1) / (len + 1);
	(void)entry;
	while (index < len)
	{
		y = space_between * (index + 1) + button_y * index;
		SDL_FillRect(g_surface,
			&(SDL_Rect){SCREEN_X / 2 - 100, y, 200, button_y},
			SDL_MapRGB(g_surface->format, 100, 100, 0)
		);
		index++;	
	}
}

void	display_menu(SDL_Surface *background, t_menu_entry *entry, char len)
{
	static char	index = 0;
	
	background = background ? background : default_background();
	/*
	if (!background || !entry) // set default background
	{
		index = 0;
		return;
	}
	*/
	if (len > MENU_MAX_ENTRY)
		return ;
	SDL_BlitSurface(
		background,
		&(SDL_Rect){0, 0, background->w, background->h},
		g_surface,
		&(SDL_Rect){0, 0, SCREEN_X, SCREEN_Y}
	);
	draw_buttons(entry, len, index);
}
