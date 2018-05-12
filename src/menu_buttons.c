#include "inc.h"
#include "menu.h"

SDL_Surface	*g_surface;
TTF_Font	*g_font;

static int			get_label_max_len(void)
{
	// retourner plutot le nombre de pixel par char
	return (8);	
}

static void draw_one_button(int y, int button_y, int button_len,int max_len)
{
	SDL_Surface	*label;
	char		*text;
	int			font_width;

	(void)max_len;
	text = "123456789";
	SDL_FillRect(g_surface,
		&(SDL_Rect){SCREEN_X / 2 - button_len / 2, y, button_len, button_y},
		SDL_MapRGB(g_surface->format, 100, 100, 0)
	);
	TTF_SizeText(g_font, text, &font_width, NULL);
	label = TTF_RenderText_Solid(g_font, text, (SDL_Color){0, 0, 0, 255});
	if (!label)
		return ;
	SDL_BlitSurface(label, NULL, g_surface,
		&(SDL_Rect){SCREEN_X / 2 - 100, y, 0, 0});
}

void		draw_buttons(t_menu_entry *entry, char len, char selected_index)
{
	char	index;
	int		space_between;
	int		y;
	int		button_y;
	int		button_len;
	int		label_max_len;

	(void)selected_index;
	(void)entry;
	button_len = 200;
	button_y = 50;
	label_max_len = get_label_max_len();
	index = 0;
	space_between = (SCREEN_Y - button_y * len + 1) / (len + 1);
	while (index < len)
	{
		y = space_between * (index + 1) + button_y * index;
		draw_one_button(y, button_y, button_len, label_max_len);
		index++;	
	}
}
