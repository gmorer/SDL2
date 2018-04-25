#include "inc.h"

void	event(void)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit_function();
	}
	return ;
}
