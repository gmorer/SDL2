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
	SDL_Surface	*error_box;
	SDL_Surface	*title_surface;
	SDL_Surface	*msg_surface;
	char		end;
	int		char_size;
	int		message_len;

	char_size = get_char_size(g_font);
	message_len = (strlen(title) > strlen(msg) ? strlen(title) : strlen(msg)) * char_size;
	error_box = SDL_CreateRGBSurface(0, message_len + ALERT_SIDE_PADDING,
		TTF_FontHeight(g_font) * 2 + ALERT_SIDE_PADDING * 4, 32,
		0x00000000, 0x0000FF00, 0x00FF0000, 0xFF000000);
	title_surface = TTF_RenderText_Solid(g_font, title, (SDL_Color){255, 255, 255, 255});
	msg_surface = TTF_RenderText_Solid(g_font, msg, (SDL_Color){255, 255, 255, 255});
	SDL_FillRect(error_box, &(SDL_Rect){0, 0, error_box->w, error_box->h}, 0xff0000);
	SDL_BlitSurface(title_surface, NULL, error_box,
			&(SDL_Rect){error_box->w / 2 - title_surface->w / 2, ALERT_SIDE_PADDING, 0, 0});
	SDL_BlitSurface(msg_surface, NULL, error_box, 
			&(SDL_Rect){error_box->w / 2 - msg_surface->w / 2, TTF_FontHeight(g_font) + ALERT_SIDE_PADDING * 2, 0, 0});
	SDL_BlitSurface(error_box, NULL, father,
			&(SDL_Rect){father->w / 2 - error_box->w / 2, father->h / 2 - error_box->h / 2, 0, 0});
	end = 0;
	SDL_UpdateWindowSurface(g_window);
	while (end == 0)
	{
		event(&event_handler, &end);
	}
	SDL_FreeSurface(title_surface);
	SDL_FreeSurface(msg_surface);
	SDL_FreeSurface(error_box);
	return 1;
}
