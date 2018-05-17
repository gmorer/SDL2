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

static int			dodge_title(t_menu_entry *entry, int index,
	int old_index, int len)
{
	if (entry[index].type != TITLE)
		return (index);
	while (index > -1 && index < len && entry[index].type == TITLE)
		index = index > old_index ? index + 1 : index - 1;
	if (index <= -1 || index >= len)
		return (old_index);
	return (index);

}

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
	);;;
	SDL_FillRect(result,
		&(SDL_Rect){0, 0, SCREEN_X, SCREEN_Y},
		SDL_MapRGB(result->format, 0, 0, 255)
	);
	return (result);
}

static void	menu_event(SDL_Event event, void *arg)
{
	t_menu_event	*data;

	data = (t_menu_event*)arg;
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_DOWN)
			(*(int*)data->index)++;
		if (event.key.keysym.sym == SDLK_UP && *((int*)(data->index)))
			(*(int*)data->index)--;
		if (VALIDATE_KEY(event.key.keysym.sym) && data->action)
			(*(int*)data->value) = data->action(*((int*)(data->value)));
	}
	return ;
}

void	display_menu(SDL_Surface *background, t_menu_entry *entry, int len)
{
	static int	index = 0;
	int			old_index;
	
	if (len > MENU_MAX_ENTRY)
		return ;
	if (!entry) // set default background
	{
		index = 0;
		return;
	}
	background = background ? background : default_background();
	old_index = index;
	index = dodge_title(entry, index, -1, len);
	event(&menu_event,
		&(t_menu_event){&index, &(entry[index].value), entry[index].action});
	index = dodge_title(entry, index, old_index, len);
	if (index == len)
		index = len - 1;
	SDL_BlitSurface(
		background,
		&(SDL_Rect){0, 0, background->w, background->h},
		g_surface,
		&(SDL_Rect){0, 0, SCREEN_X, SCREEN_Y}
	);
	draw_buttons(entry, len, index);
}
