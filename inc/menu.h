#ifndef MENU_H
# define MENU_H

# include "inc.h"

# define MENU_MAX_ENTRY 9
# define LABEL_MAX_LEN 256

typedef enum {BUTTON, TITLE, SCROLL} e_menu_type;

typedef struct	s_menu_event
{
	int			*index;
	int			*index_x;
	int 		*value;
	void		(*action)(int c);
}				t_menu_event;

typedef struct	s_menu_entry
{
	char		name[LABEL_MAX_LEN];
	e_menu_type type;
	int 		value;
	void		(*action)(int c);
}				t_menu_entry;

typedef struct	s_menu_settings
{
	SDL_Surface *background;
	SDL_Rect	*position;
	int			padding;
	int			button_with;
	int			button_height;
	TTF_Font	*font;
}				t_menu_settings;

void	draw_buttons(t_menu_settings settings, t_menu_entry *entry, int len, int selected_index,
	int *index_x);
void	display_menu(t_menu_settings settings, t_menu_entry *entry, int len);

# endif
