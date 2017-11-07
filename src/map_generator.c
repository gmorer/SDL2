#include "inc.h"

static void	print_map(char **map, int x, int y)
{
	int y_bis;
	int	x_bis;

	x_bis = 0;
	while(x_bis < x)
	{
		y_bis = 0;
		while (y_bis < y)
		{
			if (map[x_bis][y_bis] == 10)
				printf("X ");
				else
			printf("%d ", (int)map[x_bis][y_bis]);
			y_bis++;
		}
		printf("\n");
		x_bis++;
	}

}

static int	get_number(char **map, t_point point, int x_len, int y_len)
{
	int		result;

	result = 0;
	if (point.x > 0)
	{
		if (map[point.x - 1][point.y] == MINE)
			result++;
		if (point.y > 0 && map[point.x - 1][point.y - 1] == MINE)
			result++;
		if (point.y + 1 < y_len && map[point.x - 1][point.y + 1] == MINE)
			result++;
	}
	if (point.x + 1 < x_len)
	{
		if (map[point.x + 1][point.y] == MINE)
			result++;
		if (point.y > 0 && map[point.x + 1][point.y - 1] == MINE)
			result++;
		if (point.y + 1 < y_len && map[point.x + 1][point.y + 1] == MINE)
			result++;
	}
	if (point.y > 0 && map[point.x][point.y - 1] == MINE)
		result++;
	if (point.y + 1 < y_len && map[point.x][point.y + 1] == MINE)
		result++;
	return (result);
}

char		**map_generator(int x, int y, int mine, t_point start)
{
	char	**map;
	int		i;

	(void)start;
	i = 0;
	if ((map = malloc(x * sizeof(char*))) == NULL)
	{
		fprintf(stderr, "Error during map generation\n");
		return (NULL);
	}
	while (i < x)
	{
		if ((map[i] = malloc(y * sizeof(char))) == NULL)
		{
			fprintf(stderr, "Error during map generation\n");
			return (NULL);
		}
		memset(map[i], 0, y);
		i++;
	}
	while(mine)
	{
		i = (double)rand() / (double)RAND_MAX * x * y;
		map[i / x][i % x] = MINE;
		mine--;
	}
	i = x * y - 1;
	while (i >= 0)
	{
		if (map[i / x][i % x] == 0)
			map[i / x][i % x] = get_number(map, (t_point){i / x, i % x}, x, y);
		i--;
	}
	print_map(map, x, y);
	return (map);
}
