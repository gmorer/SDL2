#ifndef INC_H
# define INC_H

# define SCREEN_X 640
# define SCREEN_Y 480
# define MINE 10
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>


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
void	event(void);

#endif
