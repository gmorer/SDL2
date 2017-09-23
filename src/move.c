#include "inc.h"

int		g_fps;

void	print_map(t_image *image_tab[IMAGE_LEN], t_player *player)
{
	int		x;
	int		y;

	x = player->coord.x - (SCREEN_X / 2);
	y = player->coord.y - (SCREEN_Y / 2);
	if (player->coord.x < SCREEN_X / 2)
	{
		image_tab[player->image_id]->coord.x = player->coord.x /* (image_tab[0]->coord.w / SCREEN_X)*/;
		image_tab[player->image_id]->coord.x -= image_tab[player->image_id]->coord.w / 2;
	}
	else if (player->coord.x > image_tab[0]->coord.w - SCREEN_X / 2)
	{
		image_tab[player->image_id]->coord.x = SCREEN_X - (image_tab[0]->coord.w - player->coord.x);
		image_tab[player->image_id]->coord.x -= image_tab[player->image_id]->coord.w / 2;
	}
	else
		image_tab[0]->coord.x = -x;
	if (player->coord.y < SCREEN_Y / 2)
	{
		image_tab[player->image_id]->coord.y = player->coord.y /* (image_tab[0]->coord.w / SCREEN_X)*/;
		image_tab[player->image_id]->coord.y -= image_tab[player->image_id]->coord.h / 2;
	}
	else if (player->coord.y > image_tab[0]->coord.h - SCREEN_Y / 2)
	{
		image_tab[player->image_id]->coord.y = SCREEN_Y - (image_tab[0]->coord.h - player->coord.y);
		image_tab[player->image_id]->coord.y -= image_tab[player->image_id]->coord.h / 2;
	}
	else
		image_tab[0]->coord.y = -y;
}

void	move_player(t_image *image_tab[IMAGE_LEN], t_player *player)
{
	float		x;
	float		y;
	float		calc;
	float		game_speed;

	move_dest(image_tab, player);
	if (fabs(player->coord.x - player->dest.x) > 1 || fabs(player->coord.y - player->dest.y) > 1)
	{
		calc = sqrt(powf(player->dest.x - player->coord.x, 2) + powf(player->dest.y - player->coord.y, 2));
		game_speed = 20 * g_fps / 5000;
		if (game_speed == 0)
			game_speed = 60;
		x = (player->dest.x - player->coord.x) / calc;
		y = (player->dest.y - player->coord.y) / calc;
		x = x * player->speed / game_speed;
		y = y * player->speed / game_speed;
		player->coord.x += x;
		player->coord.y += y;
		image_tab[player->image_id]->coord.x = SCREEN_X / 2 - image_tab[player->image_id]->coord.w / 2;
		image_tab[player->image_id]->coord.y = SCREEN_Y / 2 - image_tab[player->image_id]->coord.h / 2;
		print_map(image_tab, player);
	}
	return ;
}
