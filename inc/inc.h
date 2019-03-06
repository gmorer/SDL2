#ifndef INC_H
# define INC_H

# ifdef __APPLE__
#  include <SDL.h>
#  include <SDL_ttf.h>
# else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define SCREEN_X 1280
# define SCREEN_Y 960
# define MINE 10
# define VALIDATE_KEY(i)	(i == SDLK_SPACE || \
							i == SDLK_KP_ENTER || \
							i == SDLK_RETURN || \
							i == SDLK_e )

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
# define RMASK 0xff000000
# define GMASK 0x00ff0000
# define BMASK 0x0000ff00
# define AMASK 0x000000ff
#else
# define RMASK 0x000000ff
# define GMASK 0x0000ff00
# define BMASK 0x00ff0000
# define AMASK 0xff000000
#endif
typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct	s_game
{
	char	x;
	char	y;
	char	*map;
}				t_game;

extern SDL_Window	*g_window;
extern SDL_Surface	*g_surface;
extern TTF_Font		*g_font;
extern t_game		g_game;

void exit_function(void);
int		init_sdl();
char	**map_generator(int x, int y, int mine, t_point start);
int		loop();
void	display_game(void);
void	display_options(void);
void	event(void (*f)(SDL_Event, void*), void *data);
int     get_char_size(TTF_Font *font);
int		display_alert(char *title, char *msg, SDL_Surface *father);

#endif
