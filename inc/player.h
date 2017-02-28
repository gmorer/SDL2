#ifndef _PLAYER_H
# define _PLAYER_H

typedef struct	s_fcoord
{
	float	x;
	float	y;

}								t_fcoord;

typedef struct	s_player
{
	t_fcoord				coord;
}								t_player;

t_player	*init_player();

#endif
