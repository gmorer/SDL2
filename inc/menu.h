#ifndef MENU_H
# define MENU_H

# include "inc.h"

# define MENU_MAX_ENTRY 9
# define LABEL_MAX_LEN 256
# define VALIDATE_KEY(i)	(i == SDLK_SPACE || \
							i == SDLK_KP_ENTER || \
							i == SDLK_RETURN || \
							i == SDLK_e )

typedef enum {BUTTON, TITLE, SCROLL} e_menu_type;

typedef struct	s_menu_event
{
	int		*index;
	int		*index_x;
	int 	*value;
	void	(*action)(int c);
}				t_menu_event;

typedef struct	s_menu_entry
{
	char		name[LABEL_MAX_LEN];
	e_menu_type type;
	int 		value;
	void		(*action)(int c);

}				t_menu_entry;

void	draw_buttons(t_menu_entry *entry, int len, int selected_index,
	int *index_x);
void	display_menu(SDL_Surface *background, t_menu_entry *entry, int len);

# endif
