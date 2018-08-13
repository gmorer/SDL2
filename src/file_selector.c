#include "../inc/inc.h"
#include "../inc/file_selector.h"

SDL_Surface *g_surface;

static char	*home_dir()
{
	struct passwd *user;

	user = getpwuid(getuid());
	return user->pw_dir;
}

static void	print_files(char **files, size_t len)
{
	size_t index;

	index = 0;
	while(index < len)
	{
		printf("%s\n", files[index]);
		index++;
	}
	return ;
}

char *file_selector(char *path)
{
	DIR				*dir;
	struct dirent	*file;
	size_t			buff_size;
	size_t			index;
	char			**files;
	char			**tmp_files;

	index = 0;
	buff_size = 10;
	files = malloc(buff_size * sizeof(char*));
	if (!files)
		return NULL; // malloc error
	bzero(files, buff_size * sizeof(char*));
	if (!path)
		path = home_dir();
	if (!(dir = opendir(path)))
		return (NULL); // TODO
	printf("starting...");
	while ((file = readdir(dir)))
	{
		if (!strcmp(".", file->d_name) || !strcmp("..", file->d_name))
			continue ;
		if (index >= buff_size)
		{
			tmp_files = malloc(buff_size * 2 * sizeof(char*));
			if (!tmp_files)
				return NULL; // malloc error
			bzero(tmp_files, buff_size * 2 * sizeof(char*));
			memcpy(tmp_files, files, index * sizeof(char*));
			free(files);
			files = tmp_files;
			buff_size *= 2;
		}
		files[index] = file->d_name;
		index += 1;
	}
	print_files(files, index);
	return NULL;
}
