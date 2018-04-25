#include "inc.h"

SDL_Window	*g_window;

void	exit_function()
{
	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
}

int		main()
{
	srand(time(NULL));
	if (init_sdl() == 0)
	{
		fprintf(stderr, "Error during SDL initialisation\n");
		return (0);
	}
	loop();
	map_generator(10, 10, 15, (t_point){5, 5});
	return (1);
}
