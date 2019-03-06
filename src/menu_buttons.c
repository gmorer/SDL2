#include "../inc/inc.h"
#include "../inc/menu.h"

SDL_Surface	*g_surface;

static void draw_one_title(t_menu_settings settings, t_menu_entry entry, int title_y, int char_size)
{
	SDL_Surface	*title;
	size_t		title_len;
	int			x_start;
	int h;

	h = settings.position ? settings.position->y : 0;
	title_len = strlen(entry.name) * char_size;
	if ((int)title_len > settings.position->w)
		return ;
	title = TTF_RenderText_Solid(settings.font, entry.name,
		(SDL_Color){0, 0, 0, 255});
	if (!title)
		return ;
	x_start = settings.position->w / 2 - title_len / 2;
	x_start = settings.position->x + settings.position->w / 2 - title_len / 2;
	SDL_BlitSurface(title, NULL, g_surface,
		&(SDL_Rect){x_start, h + title_y, 0, 0});
	SDL_FreeSurface(title);
}

static void draw_one_button(t_menu_settings settings, t_menu_entry entry, int y,
	int char_size, int selected)
{
	SDL_Surface	*label;
	size_t		max_len;
	size_t		text_len;
	int			margin;
	int			x_start;
	int h;

	h = settings.position ? settings.position->y : 0;
	x_start = settings.position->x + settings.position->w / 2 - settings.button_with / 2;
	if (selected)
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start - 5, h + y - 5, settings.button_with + 10, settings.button_height + 10},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
	SDL_FillRect(g_surface,
		&(SDL_Rect){x_start, h + y, settings.button_with, settings.button_height},
		SDL_MapRGB(g_surface->format, 100, 100, 0)
	);
	max_len = settings.button_with / char_size;
	text_len = strlen(entry.name);
	if (text_len > 3 && max_len < text_len)
	{
		entry.name[max_len - 3] = '.';
		entry.name[max_len - 2] = '.';
		entry.name[max_len - 1] = '.';
		entry.name[max_len] = '\0';
		margin = 0;
	}
	else
		margin = (settings.button_with - text_len * char_size) / 2;
	// label = TTF_RenderText_Solid(settings.font, entry.name,
	// 	(SDL_Color){0, 0, 0, 255});
	if (!entry.name[0])
		return ;
	label = TTF_RenderText_Solid(settings.font, entry.name,
		(SDL_Color){0, 0, 0, 255});
	if (!label)
		return ;
	SDL_BlitSurface(label, NULL, g_surface,
		&(SDL_Rect){x_start + margin, h + y, 0, 0});
	SDL_FreeSurface(label);
}

static void draw_one_scroll(t_menu_settings settings, t_menu_entry entry, int y,
	int char_size, int selected, int *index_x)
{
	int			x_start;
	char		value[12];
	size_t		len;
	SDL_Surface	*label;
	int half_with;
	int h;

	h = settings.position ? settings.position->y : 0;
	half_with = settings.button_with / 2;
	len = (sprintf(value, "%d",  entry.value) + 2) * char_size;
	x_start = settings.position->x + settings.position->w / 2 - half_with ;
	if (selected)
	{
		// el selection
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start + (*index_x == 1 ? half_with + 5 + len / 2: -5 - len / 2) ,
			h + y - 5, half_with + 5, settings.button_height + 10},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		// less button
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start - len / 2, h + y, half_with - 5, settings.button_height},
			SDL_MapRGB(g_surface->format, 100, 100, 0)
		);
		// less icon -
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start - len / 2 + (half_with - (settings.button_height - 10)) / 2,
			h + y + settings.button_height / 2 - 2, settings.button_height - 10, 4},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		// plus button
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start + half_with + 10 + len / 2,
			h + y, half_with - 5, settings.button_height},
			SDL_MapRGB(g_surface->format, 100, 100, 0)
		);
		// plus icon -
		SDL_FillRect(g_surface,
			&(SDL_Rect){
				x_start + half_with + 10 + len / 2 + (half_with - (settings.button_height - 10)) / 2,
				h + y + settings.button_height / 2 - 2, settings.button_height - 10, 4
			},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		// plus icon |
		SDL_FillRect(g_surface,
			&(SDL_Rect){
				x_start + half_with + 10 + len / 2  + settings.button_with / 4 - 2, h + y + 5,
				4, settings.button_height - 10
			},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		label = TTF_RenderText_Solid(settings.font, value, (SDL_Color){0, 0, 0, 255 });
		if (!label)
			return ;
		SDL_BlitSurface(label, NULL, g_surface,
			&(SDL_Rect){settings.position->x + settings.position->w / 2 - len / 2 + char_size,
			h + y, len, settings.button_height});
		SDL_FreeSurface(label);
	}
	else
		draw_one_button(settings, entry, y, char_size, 0);
}

void		draw_buttons(t_menu_settings settings, t_menu_entry *entry, int len, int selected_index,
	int *index_x)
{
	int	index;
	int	space_between;
	int	char_size;
	int y_start;

	char_size = get_char_size(settings.font);
	index = 0;
	space_between = (settings.position->h - settings.button_height * len + 1) / (len + 1);
	while (index < len)
	{
		y_start = space_between * (index + 1) + settings.button_height * index;
		if (entry[index].type == BUTTON)
			draw_one_button(settings, entry[index], y_start,
				char_size, selected_index == index);
		if (entry[index].type == TITLE)
			draw_one_title(settings, entry[index], y_start, char_size);
		if (entry[index].type == SCROLL)
			draw_one_scroll(settings, entry[index], y_start,
				char_size, selected_index == index, index_x);
		index++;	
	}
}
