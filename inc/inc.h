#ifndef INC_H
# define INC_H
# define SCREEN_X 640
# define SCREEN_Y 480

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include "res.h"
# include "image.h"

extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;
extern TTF_Font *g_font;

int		draw(t_image *button_tab[IMAGE_LEN]);
void	loop(void) __attribute__((noreturn));
void	close_all(t_image *image_tab[IMAGE_LEN]) __attribute__((noreturn));	
void	delet_one_image(t_image *image_tab[IMAGE_LEN], int i);

#endif
