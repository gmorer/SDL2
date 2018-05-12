#ifndef MENU_H
# define MENU_H

# include "inc.h"

# define MENU_MAX_ENTRY 9
# define LABEL_MAX_LEN 256

typedef enum {BUTTON, SCROLL} e_menu_type;

typedef struct	s_menu_entry
{
	char		*name;
	e_menu_type type;
	char 		value;
	void		(*action)(char c);

}				t_menu_entry;

void	draw_buttons(t_menu_entry *entry, char len, char selected_inex);
void	display_menu(SDL_Surface *background, t_menu_entry *entry, char len);

# endif
