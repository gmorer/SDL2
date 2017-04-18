#ifndef _STRUCT_H
# define _STRUCT_H

# include "inc.h"

typedef struct	s_fcoord
{
	float					x;
	float					y;
}								t_fcoord;

typedef struct	s_key
{
	int						mouse_x;
	int						mouse_y;
	int						right_button;
}								t_key;

typedef struct	s_texture
{
	SDL_Texture		*texture;
	SDL_Rect			src;
}								t_texture;

typedef struct	s_player
{
	int						speed;
	int						size;
	int						image_id;
	t_fcoord			coord;
	t_fcoord			dest;
}								t_player;

typedef struct	s_image
{
	SDL_Rect			coord;
	t_texture			*texture;
	t_texture			*texture_after;
	int						(*function)(struct s_image *image_tab[IMAGE_LEN], t_player *player);
	int						is_on;
	int						type;
}								t_image;

void  add_image(struct s_image *image_tab[IMAGE_LEN], SDL_Rect coord, struct s_texture *texture,
		struct s_texture *texture_after,
		int (*function)(struct s_image *image_tab[IMAGE_LEN], struct s_player *player),
		int is_interactive);

int			draw(t_image *button_tab[IMAGE_LEN]);
void    loop(t_player *player) __attribute__((noreturn));
void    close_all(t_image *image_tab[IMAGE_LEN]) __attribute__((noreturn));
void    delet_one_image(t_image *image_tab[IMAGE_LEN], int i);


#endif
