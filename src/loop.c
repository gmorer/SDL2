#include "inc.h"
#include "image.h"
#include "texture.h"
#include "event.h"
#include "res.h"

SDL_Window    *g_window;
SDL_Renderer  *g_renderer;
t_texture			*g_res[RES_LEN];

static int						yolo(t_image *image_tab[IMAGE_LEN])
{
	(void)image_tab;
	write(1, "yolo\n", 5);
	return (1);
}

static int						yolo_play(t_image *image_tab[IMAGE_LEN])
{
	add_image(image_tab, (SDL_Rect){rand() % SCREEN_X, rand() % SCREEN_Y, 45, 45},
	    g_res[IMAGE], NULL, NULL, IMAGE);
	return (1);
}
static int						yolo_exit(t_image *image_tab[IMAGE_LEN])
{
	close_all(image_tab);
}

static int   test_menu(t_image *image_tab[IMAGE_LEN])
{
	add_image(image_tab, (SDL_Rect){0, 0, SCREEN_X, SCREEN_Y},
	    g_res[IMAGE], NULL, NULL, IMAGE);
	add_image(image_tab, (SDL_Rect){290, 140, 100, 40},
	    g_res[BLACK], g_res[SELECTED], &yolo_play, BUTTON);
	add_image(image_tab, (SDL_Rect){290, 190, 100, 40},
	    g_res[BLACK], g_res[SELECTED], &yolo, BUTTON);
	add_image(image_tab, (SDL_Rect){290, 240, 100, 40},
	    g_res[BLACK], g_res[SELECTED], &yolo_exit, BUTTON);
	add_image(image_tab, (SDL_Rect){300, 150, 80, 20},
	    load_txt("Jouer", (SDL_Color){0, 0, 0, 0}), NULL, NULL, TEXT);
	add_image(image_tab, (SDL_Rect){300, 200, 80, 20},
	    load_txt("Option", (SDL_Color){0, 0, 0, 0}), NULL, NULL, TEXT);
	add_image(image_tab, (SDL_Rect){300, 250, 80, 20},
	    load_txt("Quitter", (SDL_Color){0, 0, 0, 0}), NULL, NULL, TEXT);
	return (0);
}

void    loop(void)
{
	SDL_Event	event;
	t_image		*image_tab[IMAGE_LEN];
	int				i;

	srand(time(NULL));
	i = 0;
	while (i < IMAGE_LEN)
	{
		image_tab[i] = NULL;
		i++;
	}
	test_menu(image_tab);
	while(1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				close_all(image_tab);
			mouse_event(&event, image_tab);
		}
		SDL_RenderClear(g_renderer);
		draw(image_tab);
		SDL_RenderPresent(g_renderer);
	}
}
