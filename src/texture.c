#include "inc.h"
#include "texture.h"

extern SDL_Renderer *g_renderer;
extern TTF_Font *g_font;

t_texture		*load_png(char *path)
{
	t_texture		*rslt;
	SDL_Texture	*texture;
	SDL_Surface *surface;

	rslt = (t_texture*)malloc(sizeof(t_texture));
	surface = IMG_Load(path);
	if (!surface || !rslt)
		return (NULL);
	rslt->src.x = 0;
	rslt->src.y = 0;
	rslt->src.h = surface->h;
	rslt->src.w = surface->w;
	texture = SDL_CreateTextureFromSurface(g_renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		return (NULL);
	rslt->texture = texture;
	return (rslt);
}

t_texture   *load_bmp(char *path)
{
	t_texture		*rslt;
	SDL_Texture	*texture;
	SDL_Surface *surface;

	rslt = (t_texture*)malloc(sizeof(t_texture));
	surface = SDL_LoadBMP(path);
	if (!surface || !rslt)
		return (NULL);
	rslt->src.x = 0;
	rslt->src.y = 0;
	rslt->src.h = surface->h;
	rslt->src.w = surface->w;
	texture = SDL_CreateTextureFromSurface(g_renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		return (NULL);
	rslt->texture = texture;
	return (rslt);
}

t_texture	*load_txt(char *text, SDL_Color color)
{
	t_texture		*rslt;
	SDL_Texture	*texture;
	SDL_Surface	*surface;

	rslt = (t_texture*)malloc(sizeof(t_texture));
	surface = TTF_RenderText_Solid(g_font, text, color);
	if (!surface || !rslt)
		return (NULL);
	rslt->src.x = 0;
	rslt->src.y = 0;
	rslt->src.h = surface->h;
	rslt->src.w = surface->w;
	texture = SDL_CreateTextureFromSurface(g_renderer, surface);
		SDL_FreeSurface(surface);
	if (!texture)
		return (NULL);
	rslt->texture = texture;
	return (rslt);
}
