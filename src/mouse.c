#include "inc.h"
#include "event.h"

void		take_player_dest(SDL_Event *event, t_image *image_tab[IMAGE_LEN], t_player *player)
{
		if (player->coord.x < SCREEN_X / 2)
			player->dest.x = event->button.x;
		else if (player->coord.x > image_tab[0]->coord.w - SCREEN_X / 2)
			player->dest.x = event->button.x + (image_tab[0]->coord.w - SCREEN_X);
		else
			player->dest.x = event->button.x - SCREEN_X / 2 + player->coord.x;
		if (player->coord.y < SCREEN_Y / 2)
			player->dest.y = event->button.y;
		else if (player->coord.y > image_tab[0]->coord.h - SCREEN_Y / 2)
			player->dest.y = event->button.y + (image_tab[0]->coord.h - SCREEN_Y);
		else
			player->dest.y = event->button.y - SCREEN_Y / 2 + player->coord.y;
		if (player->dest.x < 0)
			player->dest.x = 0;
		if (player->dest.x > image_tab[0]->coord.w)
			player->dest.x = image_tab[0]->coord.w;
		if (player->dest.y < 0)
			player->dest.y = 0;
		if (player->dest.y > image_tab[0]->coord.h)
			player->dest.y = image_tab[0]->coord.h;
}

void		mouse_event(SDL_Event *event, t_image *image_tab[IMAGE_LEN], t_player *player)
{
	int				i;

	i = IMAGE_LEN - 1;
	while (i && image_tab[i] == NULL)
		i--;
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && image_tab[3] == NULL)
		take_player_dest(event, image_tab, player);
	if (event->type == SDL_MOUSEBUTTONUP &&
			event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_RELEASED)
	{
		while (i > -1 && image_tab[i])
		{
			if (image_tab[i]->type == BUTTON && event->button.x >= image_tab[i]->coord.x &&
					event->button.x <= image_tab[i]->coord.x + image_tab[i]->coord.w &&
					event->button.y >= image_tab[i]->coord.y &&
					event->button.y <= image_tab[i]->coord.y + image_tab[i]->coord.h)
				{
					image_tab[i]->function(image_tab, player);
					break;
				}
			i--;
		}

	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		while (i && image_tab[i])
		{
			if (image_tab[i]->type == BUTTON && event->button.x >= image_tab[i]->coord.x &&
					event->button.x <= image_tab[i]->coord.x + image_tab[i]->coord.w &&
					event->button.y >= image_tab[i]->coord.y &&
					event->button.y <= image_tab[i]->coord.y + image_tab[i]->coord.h)
			{
				image_tab[i]->is_on = 1;
			}
			else
			{
				image_tab[i]->is_on = 0;
			}
			i--;
		}
	}
	return ;
}
