#ifndef FILE_SELECTOR_H
# define FILE_SELECTOR_H

# include <pwd.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "inc.h"

typedef enum { NO_EVENT, ESCAPE, UP, DOWN, ENTER, PREVIOUS } e_file_selector_action;

typedef struct	s_selector_settings
{
	SDL_Surface	*father;
	SDL_Rect	position;
	int			padding;
	unsigned int	background_color;
	unsigned int	selector_color;
	unsigned int	path_background;
	SDL_Color	text_color;

}				t_selector_settings;

char *file_selector(char *path, t_selector_settings settings);

#endif
