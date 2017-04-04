#include "inc.h"

SDL_Window		*g_window;
SDL_Renderer	*g_renderer;
TTF_Font			*g_font;
t_texture			*g_res[RES_LEN];

void		delet_one_image(t_image *image_tab[IMAGE_LEN], int i)
{
	if (image_tab[i]->type == TEXT && image_tab[i]->texture)
		SDL_DestroyTexture(image_tab[i]->texture->texture);
	free(image_tab[i]);
	image_tab[i] = NULL;
	return ;
}

void		close_all(t_image *image_tab[IMAGE_LEN])
{
	int	i;

	i = 0;
	while (i < RES_LEN)
	{
		if (g_res[i])
			SDL_DestroyTexture(g_res[i]->texture);
		i++;
	}
	i = 0;
	while (i < IMAGE_LEN && image_tab[i])
	{
		delet_one_image(image_tab, i);
		i++;
	}
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	TTF_CloseFont(g_font);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(0);
}
