#include "inc.h"

void	print_map(t_image *image_tab[IMAGE_LEN], t_player *player)
{
	int		x;
	int		y;

	//delet_one_image(image_tab, 0);
	x = player->coord.x - (SCREEN_X / 2);
	y = player->coord.y - (SCREEN_Y / 2);
	(void)player;
	image_tab[0]->coord.x = -x;
	image_tab[0]->coord.y = -y;
	//add_image(image_tab, (SDL_Rect){-x, -y, g_res[MAP]->src.w, g_res[MAP]->src.h},
		//	            g_res[MAP], NULL, NULL, IMAGE);
}

void	move_player(t_image *image_tab[IMAGE_LEN], t_player *player)
{
	float		x;
	float		y;
	float		calc;

	if (abs(player->coord.x - player->dest.x) > 1 || abs(player->coord.y - player->dest.y) > 1)
	{
		calc = sqrt(powf(player->dest.x - player->coord.x, 2) + powf(player->dest.y - player->coord.y, 2));
		x = (player->dest.x - player->coord.x) / calc;
		y = (player->dest.y - player->coord.y) / calc;
		x = x * 2;
		y = y * 2;
		player->coord.x += x;
		player->coord.y += y;
		print_map(image_tab, player);
	}
	return ;
}
