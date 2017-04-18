#ifndef _PLAYER_H
# define _PLAYER_H

# include "struct.h"
# include "image.h"

t_player	*init_player();

void			move_player(t_image *image_tab[IMAGE_LEN], t_player *player);
void			move_dest(t_image *image_tab[IMAGE_LEN], t_player *player);

#endif
