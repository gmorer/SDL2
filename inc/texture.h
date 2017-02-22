#ifndef TEXTURE_H
# define TEXTURE_H

# include "inc.h"

typedef struct	s_texture
{
	SDL_Texture		*texture;
	SDL_Rect			src;
}								t_texture;

t_texture *load_bmp(char *path);
t_texture *load_png(char *path);
t_texture *load_txt(char *txt, SDL_Color color);

#endif
