#ifndef _PLAYER_H
# define _PLAYER_H

typedef struct	s_fcoord
{
	float	x;
	float	y;

}								t_fcoord;

typedef struct	s_player
{
	int							speed;
	int							size;
	int							image_id;
	t_fcoord				coord;
	t_fcoord				dest;
}								t_player;

t_player	*init_player();
void			move_player();

#endif
