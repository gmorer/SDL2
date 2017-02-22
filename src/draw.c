#include "inc.h"
#include "image.h"

SDL_Renderer  *g_renderer;

int   draw(t_image *image_tab[IMAGE_LEN])
{
	int				i;

	i = 0;
	while (i < IMAGE_LEN && image_tab[i])
	{
		if (image_tab[i]->is_on && image_tab[i]->texture_after)
			SDL_RenderCopy(g_renderer, image_tab[i]->texture_after->texture,
					&(image_tab[i]->texture->src), &(image_tab[i]->coord));
		else
			SDL_RenderCopy(g_renderer, image_tab[i]->texture->texture,
					&(image_tab[i]->texture->src), &(image_tab[i]->coord));
		i++;
	}
	return (1);
}
