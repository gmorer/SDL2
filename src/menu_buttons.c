#include "inc.h"
#include "menu.h"

SDL_Surface	*g_surface;
TTF_Font	*g_font;

static int			get_char_size(void)
{
	int		w;
	char	*alphabet = "abcdefghijklmnopqrstuvwxyz ";
	char	alphabet_len = 27;

	TTF_SizeText(g_font, alphabet, &w, NULL);
	if (!w)
		return (20);
	return (w / alphabet_len);	
}

static void draw_one_button(int y, int button_y, int button_len,int char_size,
	char selected)
{
	SDL_Surface	*label;
	char		text[] = "12678";
	size_t		max_len;
	size_t		text_len;
	int			margin;
	int			x_start;

	x_start = SCREEN_X / 2 - button_len / 2;
	if (selected)
		SDL_FillRect(g_surface,
			&(SDL_Rect){x_start - 5, y -5, button_len + 10, button_y + 10},
			SDL_MapRGB(g_surface->format, 0, 0, 0)
		);
	SDL_FillRect(g_surface,
		&(SDL_Rect){x_start, y, button_len, button_y},
		SDL_MapRGB(g_surface->format, 100, 100, 0)
	);
	max_len = button_len / char_size;
	text_len = strlen(text);
	if (text_len > 3 && max_len < text_len)
	{
		printf("text_len:%lu, max_len:%lu\n", text_len, max_len);
		text[max_len - 3] = '.';
		text[max_len - 2] = '.';
		text[max_len - 1] = '.';
		text[max_len] = '\0';
	}
	margin = (button_len - text_len * char_size) / 2;
	label = TTF_RenderText_Solid(g_font, text, (SDL_Color){0, 0, 0, 255});
	if (!label)
		return ;
	SDL_BlitSurface(label, NULL, g_surface,
		&(SDL_Rect){x_start + margin, y, 0, 0});
	SDL_FreeSurface(label);
}

void		draw_buttons(t_menu_entry *entry, char len, char selected_index)
{
	char	index;
	int		space_between;
	int		y;
	int		button_y;
	int		button_len;
	int		char_size;;

	(void)selected_index;
	(void)entry;
	button_len = 200;
	button_y = 50;
	char_size = get_char_size();
	index = 0;
	space_between = (SCREEN_Y - button_y * len + 1) / (len + 1);
	while (index < len)
	{
		y = space_between * (index + 1) + button_y * index;
		draw_one_button(y, button_y, button_len, char_size,
			selected_index == index);
		index++;	
	}
}
