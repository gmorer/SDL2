#ifndef RES_H
# define RES_H

# include "texture.h"

enum {
	BLACK,
	C,
	SELECTED,
	PNG,
	RES_LEN
};

extern t_texture *g_res[RES_LEN];

void	init_res(void);

#endif
