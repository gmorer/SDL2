#include "player.h"
#include "inc.h"

t_player		*init_player(void)
{
	t_player	*rslt;

	if(!(rslt = (t_player*)malloc(sizeof(t_player))))
		return (NULL);
	rslt->coord = (t_fcoord){0, 0};
	return (rslt);
}
