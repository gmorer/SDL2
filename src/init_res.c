#include "inc.h"

t_texture	*g_res[RES_LEN];

void		init_res(void)
{
	int i;

	i = 0;
	while (i < RES_LEN)
	{
		g_res[i] = NULL;
		i++;
	}
	g_res[BLACK] = load_bmp("res/black.bmp");
	g_res[C] = load_bmp("res/c.bmp");
	g_res[PNG] = load_png("res/png.png");
	g_res[SELECTED] = load_bmp("res/selected.bmp");
	return ;
}
