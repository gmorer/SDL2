#include "../inc/inc.h"
#include "../inc/menu.h"

SDL_Surface	*g_surface;

static int			get_char_size(TTF_Font *font)
{
	int		w;
	char	*alphabet = "abcdefghijklmnopqrstuvwxyz ";
	int		alphabet_len = 27;

	TTF_SizeText(font, alphabet, &w, NULL);
	if (!w)
		return (20);
	return (w / alphabet_len);	
}

static void draw_one_title(SDL_Rect *rect, TTF_Font *font, t_menu_entry entry, int title_y, int char_size)
{
	SDL_Surface	*title;
	size_t		title_len;
	int			x_start;

	if (!entry.name)
		return ;
	title_len = strlen(entry.name) * char_size;
	if ((int)title_len > rect->w)
		return ;
	title = TTF_RenderText_Solid(font, entry.name,
		(SDL_Color){0, 0, 0, 255});
	if (!title)
		return ;
	x_start = rect->w / 2 - title_len / 2;
	SDL_BlitSurface(title, NULL, g_surface,
		&(SDL_Rect){x_start, title_y, 0, 0});
	SDL_FreeSurface(title);
}

static void draw_one_button(SDL_Rect *rect, TTF_Font *font, t_menu_entry entry, int y, int button_y,
	int button_len, int char_size, int selected)
{
	SDL_Surface	*label;
	size_t		max_len;
	size_t		text_len;
	int				margin;
	int				x_start;

	x_start = rect->x + rect->w / 2 - button_len / 2;
	if (selected)
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start - 5, y - 5, button_len + 10, button_y + 10},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
	SDL_FillRect(g_surface,
		&(SDL_Rect){x_start, y, button_len, button_y},
		SDL_MapRGB(g_surface->format, 100, 100, 0)
	);
	max_len = button_len / char_size;
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
		margin = (button_len - text_len * char_size) / 2;
	label = TTF_RenderText_Solid(font, entry.name,
		(SDL_Color){0, 0, 0, 255});
	if (!label)
		return ;
	SDL_BlitSurface(label, NULL, g_surface,
		&(SDL_Rect){x_start + margin, y, 0, 0});
	SDL_FreeSurface(label);
}

static void draw_one_scroll(SDL_Rect *rect, TTF_Font *font, t_menu_entry entry, int y, int button_y,
	int button_len, int char_size, int selected, int *index_x)
{
	int			x_start;
	char		value[12];
	size_t		len;
	SDL_Surface	*label;

	len = (sprintf(value, "%d",  entry.value) + 2) * char_size;
	x_start = rect->x + rect->w / 2 - button_len / 2 ;
	if (selected)
	{
		// el selection
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start + (*index_x == 1 ? button_len / 2 + 5 + len / 2: -5 - len / 2) ,
			y - 5, button_len / 2 + 5, button_y + 10},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		// less button
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start - len / 2, y, button_len / 2 - 5, button_y},
			SDL_MapRGB(g_surface->format, 100, 100, 0)
		);
		// less icon -
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start - len / 2 + (button_len / 2 - (button_y - 10)) / 2, y + button_y / 2 - 2, button_y - 10, 4},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		// plus button
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start + button_len / 2 + 10 + len / 2,
			y, button_len / 2 - 5, button_y},
			SDL_MapRGB(g_surface->format, 100, 100, 0)
		);
		// plus icon -
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start + button_len / 2 + 10 + len / 2 + (button_len / 2 - (button_y - 10)) / 2, y + button_y / 2 - 2, button_y - 10, 4},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		// plus icon |
		SDL_FillRect(g_surface,
		&(SDL_Rect){x_start + button_len / 2 + 10 + len / 2  + button_len / 4 - 2, y + 5,   4, button_y - 10},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
		label = TTF_RenderText_Solid(font, value, (SDL_Color){0, 0, 0, 255 });
		if (!label)
			return ;
		SDL_BlitSurface(label, NULL, g_surface, &(SDL_Rect){rect->x + rect->w / 2 - len / 2 + char_size,  y, len, button_y});
		SDL_FreeSurface(label);
	}
	else
		draw_one_button(rect, font, entry, y, button_y, button_len, char_size, 0);
}

void		draw_buttons(SDL_Rect *rect, TTF_Font *font, t_menu_entry *entry, int len, int selected_index,
	int *index_x)
{
	int	index;
	int	space_between;
	int	button_y;
	int	button_len;
	int	char_size;;

	button_len = rect->w / 2;
	button_y = TTF_FontHeight(font) * 1.25;
	char_size = get_char_size(font);
	index = 0;
	space_between = (rect->h - button_y * len + 1) / (len + 1);
	while (index < len)
	{
		if (entry[index].type == BUTTON)
			draw_one_button(rect, font, entry[index],
				space_between * (index + 1) + button_y * index,
				button_y, button_len, char_size, selected_index == index);
		if (entry[index].type == TITLE)
			draw_one_title(rect, font, entry[index],
				space_between * (index + 1) + button_y * index,
				char_size);
		if (entry[index].type == SCROLL)
			draw_one_scroll(rect, font, entry[index],
				space_between * (index + 1) + button_y * index,
				button_y, button_len, char_size, selected_index == index,
				index_x);
		index++;	
	}
}
