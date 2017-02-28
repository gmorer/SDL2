#include "inc.h"
#include "image.h"

void  add_image(t_image *image_tab[IMAGE_LEN], SDL_Rect coord, t_texture *texture,
    t_texture *texture_after, int (*function)(t_image *image_tab[IMAGE_LEN], t_player *player), int type)
{
	t_image	*rslt;
	int			i;

	i = 0;
	while (i < IMAGE_LEN && image_tab[i])
		i++;
	if (i == IMAGE_LEN)
	{
		write(2, "can't add image to the queue : not enought space\n", 49);
		return ;
	}
  rslt = (t_image*)malloc(sizeof(t_image));
  if (!rslt)
  {
    write(2, "malloc error\n", 13);
    return ;
  }
  rslt->coord = coord;
  rslt->texture = texture;
  rslt->texture_after = texture_after;
  rslt->function = function;
  rslt->is_on = 0;
  rslt->type = type;
	image_tab[i] = rslt;
  return ;
}
