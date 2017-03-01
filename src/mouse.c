#include "inc.h"
#include "event.h"

void		mouse_event(SDL_Event *event, t_image *image_tab[IMAGE_LEN], t_player *player)
{
	int				i;

	i = IMAGE_LEN - 1;
	while (i && image_tab[i] == NULL)
		i--;
	if (event->type == SDL_MOUSEBUTTONUP &&
			event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_RELEASED)
	{
		player->dest.x = event->button.x - SCREEN_X / 2 + player->coord.x;
		player->dest.y = event->button.y - SCREEN_Y / 2 + player->coord.y;
		while (i && image_tab[i])
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
