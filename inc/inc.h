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

int		init_sdl();
char	**map_generator(int x, int y, int mine, t_point start);
int		loop();
void	display_game(void);
void	display_options(void);
void	exit_function(void);
void	event(void (*f)(SDL_Event, void*), void *data);
int     get_char_size(TTF_Font *font);
int		display_alert(char *title, char *msg, SDL_Surface *father);

#endif
