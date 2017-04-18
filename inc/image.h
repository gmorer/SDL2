#ifndef BUTTON_H
# define BUTTON_H

# include "struct.h"
# include "texture.h"
# include "player.h"

enum {
	TEXT,
	IMAGE,
	BUTTON
};
/*
void  add_image(struct s_image *image_tab[IMAGE_LEN], SDL_Rect coord, struct s_texture *texture,
		    struct s_texture *texture_after,
				int (*function)(struct s_image *image_tab[IMAGE_LEN], struct s_player *player), int is_interactive);
*/
#endif
