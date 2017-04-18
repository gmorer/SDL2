#ifndef TEXTURE_H
# define TEXTURE_H

# include "inc.h"
# include "struct.h"

struct s_texture *load_bmp(char *path);
struct s_texture *load_png(char *path);
struct s_texture *load_txt(char *txt, SDL_Color color);

#endif
