#include "inc.h"
#include "event.h"

t_key		*g_key;

void		take_player_dest(t_image *image_tab[IMAGE_LEN], t_player *player)
{
	if (player->coord.x < SCREEN_X / 2)
		player->dest.x = g_key->mouse_x;
	else if (player->coord.x > image_tab[0]->coord.w - SCREEN_X / 2)
		player->dest.x = g_key->mouse_x + (image_tab[0]->coord.w - SCREEN_X);
	else
		player->dest.x = g_key->mouse_x - SCREEN_X / 2 + player->coord.x;
	if (player->coord.y < SCREEN_Y / 2)
		player->dest.y = g_key->mouse_y;
	else if (player->coord.y > image_tab[0]->coord.h - SCREEN_Y / 2)
		player->dest.y = g_key->mouse_y + (image_tab[0]->coord.h - SCREEN_Y);
	else
		player->dest.y = g_key->mouse_y - SCREEN_Y / 2 + player->coord.y;
	if (player->dest.x < 0)
		player->dest.x = 0;
	if (player->dest.x > image_tab[0]->coord.w)
		player->dest.x = image_tab[0]->coord.w;
	if (player->dest.y < 0)
		player->dest.y = 0;
	if (player->dest.y > image_tab[0]->coord.h)
		player->dest.y = image_tab[0]->coord.h;
}

static void	button_on(t_image *image_tab[IMAGE_LEN])
{
	int		i;

	i = IMAGE_LEN - 1;
	while (i && image_tab[i] == NULL)
		i--;
	while (i && image_tab[i])
	{
		if (image_tab[i]->type == BUTTON && g_key->mouse_x >= image_tab[i]->coord.x &&
				g_key->mouse_x <= image_tab[i]->coord.x + image_tab[i]->coord.w &&
				g_key->mouse_y >= image_tab[i]->coord.y &&
				g_key->mouse_y <= image_tab[i]->coord.y + image_tab[i]->coord.h)
		{
			image_tab[i]->is_on = 1;
		}
		else
			image_tab[i]->is_on = 0;
		i--;
	}
	return ;
}

void		move_dest(t_image *image_tab[IMAGE_LEN], t_player *player)
{
	if (g_key->right_button == 1 && image_tab[3] == NULL)
		take_player_dest(image_tab, player);
}

void		mouse_event(SDL_Event *event, t_image *image_tab[IMAGE_LEN], t_player *player)
{
	int				i;
	int				save;

	save = g_key->right_button;
	/*
	 ** g_key attribution
	 */
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT
			&& event->button.state == SDL_PRESSED)
		g_key->right_button = 1;	
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT
			&& event->button.state == SDL_RELEASED)
		g_key->right_button = 0;
	if (event->type == SDL_MOUSEMOTION)
	{
		g_key->mouse_x = event->button.x;
		g_key->mouse_y = event->button.y;
		button_on(image_tab);
	}
	/*
	 ** test if you release on button
	 */
	if (save == 1 && g_key->right_button == 0)
	{
		i = IMAGE_LEN - 1;
		while (i && image_tab[i] == NULL)
			i--;
		while (i > -1 && image_tab[i])
		{
			if (image_tab[i]->type == BUTTON && event->button.x >= image_tab[i]->coord.x &&
					event->button.x <= image_tab[i]->coord.x + image_tab[i]->coord.w &&
					event->button.y >= image_tab[i]->coord.y &&
					event->button.y <= image_tab[i]->coord.y + image_tab[i]->coord.h)
			{
				image_tab[i]->function(image_tab, player);
				break ;
			}
			i--;
		}
	}
	return ;
}
