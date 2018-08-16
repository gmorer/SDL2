#include "../inc/inc.h"

int		get_char_size(TTF_Font *font)
{
	int             w;
 	char    *alphabet = "abcdefghijklmnopqrstuvwxyz ";
	int             alphabet_len = 27;

    TTF_SizeText(font, alphabet, &w, NULL);
    if (!w)
    	return (20);
    return (w / alphabet_len);
}
