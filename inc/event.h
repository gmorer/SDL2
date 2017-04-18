#ifndef EVENT_H
# define EVENT_H

# include "struct.h"

extern	t_key *g_key;

void	mouse_event(SDL_Event *event, t_image *image_tab[IMAGE_LEN], t_player *player);

#endif
