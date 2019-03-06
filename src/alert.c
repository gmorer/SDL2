#include "../inc/inc.h"

# define ALERT_SIDE_PADDING 20

TTF_Font	*g_font;
SDL_Window	*g_window;

static void  event_handler(SDL_Event event, void *data)
{
	int *ret;

	ret = data;
	if (event.type == SDL_KEYUP && VALIDATE_KEY(event.key.keysym.sym))
		*ret = 1;
}

int display_alert(char *title, char *msg, SDL_Surface *father)
{
	SDL_Surface	*title_surface;
	SDL_Surface	*msg_surface;
	char		end;
	int		char_size;
	int		message_len;
	SDL_Rect	box;

	char_size = get_char_size(g_font);
	message_len = (strlen(title) > strlen(msg) ? strlen(title) : strlen(msg)) * char_size;
	box.w = message_len + ALERT_SIDE_PADDING;
	box.h = TTF_FontHeight(g_font) * 2 + ALERT_SIDE_PADDING * 4;
	box.x = father->w / 2 - box.w / 2;
	box.y = father->h / 2 - box.h / 2;
	title_surface = TTF_RenderText_Solid(g_font, title, (SDL_Color){255, 255, 255, 255});
	msg_surface = TTF_RenderText_Solid(g_font, msg, (SDL_Color){255, 255, 255, 255});
	SDL_FillRect(father, &box, 0xff0000);
	SDL_BlitSurface(title_surface, NULL, father,
			&(SDL_Rect){box.x + box.w / 2 - title_surface->w / 2,
			box.y + ALERT_SIDE_PADDING, 0, 0});
	SDL_BlitSurface(msg_surface, NULL, father, 
			&(SDL_Rect){box.x + box.w / 2 - msg_surface->w / 2,
			box.y + TTF_FontHeight(g_font) + ALERT_SIDE_PADDING * 2, 0, 0});
	end = 0;
	SDL_FreeSurface(title_surface);
	SDL_FreeSurface(msg_surface);
	SDL_UpdateWindowSurface(g_window);
	while (end == 0)
	{
		event(&event_handler, &end);
	}
	return 1;
}
