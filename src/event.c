#include "../inc/inc.h"

void	event(void (*f)(SDL_Event, void*), void* data)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit_function();
		if (data)
			f(event, data);
	}
	return ;
}
