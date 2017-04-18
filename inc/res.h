#ifndef RES_H
# define RES_H

# include "struct.h"
# include "texture.h"

enum {
	BLACK,
	C,
	SELECTED,
	PNG,
	MAP,
	HERO,
	RES_LEN
};

extern struct s_texture *g_res[RES_LEN];

void	init_res(void);

#endif
