#ifndef BUTTON_H
# define BUTTON_H

# include "texture.h"

# define IMAGE_LEN 50

enum {
	TEXT,
	IMAGE,
	BUTTON
};

typedef struct s_image
{
	SDL_Rect			coord;
	t_texture			*texture;
	t_texture			*texture_after;
	int						(*function)(struct s_image *image_tab[IMAGE_LEN]);
	int						is_on;
	int						type;
}              t_image;

void  add_image(t_image *image_tab[IMAGE_LEN], SDL_Rect coord, t_texture *texture,
		    t_texture *texture_after, int (*function)(t_image *image_tab[IMAGE_LEN]), int is_interactive);

#endif
