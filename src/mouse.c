#include "inc.h"
#include "event.h"

void		mouse_event(SDL_Event *event, t_image *image_tab[IMAGE_LEN])
{
	int				i;

	i = IMAGE_LEN - 1;
	while (i && image_tab[i] == NULL)
		i--;
	//printf("i = %d\n", i);
	if(i == 0)
		write(1, "lol", 3);
	if (event->type == SDL_MOUSEBUTTONUP &&
			event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_RELEASED)
	{
		while (i && image_tab[i])
		{
			if (image_tab[i]->type == BUTTON && event->button.x >= image_tab[i]->coord.x &&
					event->button.x <= image_tab[i]->coord.x + image_tab[i]->coord.w &&
					event->button.y >= image_tab[i]->coord.y &&
					event->button.y <= image_tab[i]->coord.y + image_tab[i]->coord.h)
				{
		//			printf("i = %d\n", i);
					image_tab[i]->function(image_tab);
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
