#include "../inc/inc.h"
#include "../inc/menu.h"

SDL_Surface	*g_surface;
TTF_Font	*g_font;

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

static SDL_Surface	*default_background(t_menu_settings settings)
{
	SDL_Surface		*result;
	int w;
	int h;

	w = settings.position ? settings.position->w : SCREEN_X;
	h = settings.position ? settings.position->h : SCREEN_Y;

	result = SDL_CreateRGBSurface(
		0,
		w,
		h,
		32,
		RMASK,
		GMASK,
		BMASK,
		AMASK
	);;;
	SDL_FillRect(result,
		&(SDL_Rect){0, 0, w, h},
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
		else if (event.key.keysym.sym == SDLK_UP && *((int*)(data->index)))
			(*(int*)data->index)--;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			(*(int*)data->index_x) = 1;
		else if (event.key.keysym.sym == SDLK_LEFT)
			(*(int*)data->index_x) = -1;
		else if (VALIDATE_KEY(event.key.keysym.sym) && data->action)
		{
			(*(int*)data->value) += (*(int*)data->index_x);
			data->action(*((int*)(data->value)));
		}
	}
	return ;
}

void	display_menu(t_menu_settings settings, t_menu_entry *entry, int len)
{
	int		old_index;
	static int	index_x = -1;
	
	// init_settings(&settings);
	if (len > MENU_MAX_ENTRY)
		return ;
	if (!entry) // set default background
	{
		settings.index = 0;
		index_x = -1;
		return;
	}
	if (!settings.font)
		settings.font = g_font;
	if (!settings.background)
		settings.background = default_background(settings);
	if (!settings.position)
		settings.position = &(SDL_Rect){0, 0, SCREEN_X, SCREEN_Y};
	if (!settings.button_with)
		settings.button_with = settings.position->w / 2;
	if (!settings.button_height)
		settings.button_height = TTF_FontHeight(settings.font) * 1.25;
	while (!entry[len - 1].value)
	{
		old_index = settings.index;
		settings.index = dodge_title(entry, settings.index, -1, len);
		event(&menu_event,
			&(t_menu_event){&(settings.index), &index_x,
			&(entry[settings.index].value), entry[settings.index].action});
		if (settings.index >= len)
			settings.index = len - 1;
		settings.index = dodge_title(entry, settings.index, old_index, len);
		if (settings.index == len)
			settings.index = len - 1;
		SDL_BlitSurface(
			settings.background,
			NULL,
			g_surface,
			settings.position
			//&(SDL_Rect){0, 0, SCREEN_X, SCREEN_Y}
		);
		draw_buttons(settings, entry, len, settings.index, &index_x);
		SDL_UpdateWindowSurface(g_window);
	}
	SDL_FreeSurface(settings.background);
}
