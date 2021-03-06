#include "../inc/file_selector.h"

TTF_Font	*g_font;
SDL_Window		*g_window;

// This do not wotk with file with "/" in the name :(
static char	*remove_last(char *path)
{
	size_t len;
	size_t index;

	if(!path)
		return path;
	// Test if path is root
	if(path[0] == '/' && !path[1])
	{
		return path;
	}
	len = strlen(path);
	index = (size_t)(strrchr(path, '/') - path);
	if (!index)
	{
		path[0] = '/';
		path[1] = 0;
		return path;
	}
	else if (len == index)
	{
		path[index] = 0;
		index = (size_t)(strrchr(path, '/') - path);
	}
	path[index] = 0;
	return path;
}

static char	*check_file(t_selector_settings settings, char *path, char *old_path)
{
	struct stat	statbuf;

	if (access(path, R_OK) == -1)
	{
		free(path);
		display_alert("error", "Cannot read the path", settings.father);
		return file_selector(old_path, settings);
	}
	if (stat(path, &statbuf) == -1)
	{
		free(path);
		display_alert("error", "Cannot read the path's stats", settings.father);
		return file_selector(old_path, settings);
	}
	free(old_path);
	if (S_ISDIR(statbuf.st_mode))
		return file_selector(path, settings);
	return path;
}


static char	*free_everything(SDL_Surface *files_list, char **files, char *selected, char *path,
	t_selector_settings settings)
{
	char	*result;
	size_t	path_len;
	size_t	selected_len;

	if (!selected)
	{
		free(path);
		free(files);
		return NULL;
	}
	if (!strcmp(selected, ".."))
		result = strdup(remove_last(path));
	else {
		path_len = strlen(path);
		path_len -= path_len == 1 ? 1 : 0;
		selected_len = strlen(selected);
		result = malloc((path_len + selected_len + 2) * sizeof(char));
		strcpy(result, path);
		result[path_len] = '/';
		strcpy(result + path_len + 1, selected);
	}
	free(files);
	printf("result: %s\n", result);
	SDL_FreeSurface(files_list);
	return (check_file(settings, result, path));
}

static char	*home_dir()
{
	struct passwd *user;

	user = getpwuid(getuid());
	return strdup(user->pw_dir);
}

static void	print_files(char **files, size_t len)
{
	size_t index;

	(void)files;
	index = 0;
	while(index < len)
	{
	//	printf("%s\n", files[index]);
		index++;
	}
	return ;
}

static int	strcmp_wrapper(const void *str1, const void *str2)
{
	return strcmp(*(const char**)str1, *(const char**)str2);
}

static char **get_files(char **path, size_t *len)
{
	DIR				*dir;
	struct dirent	*file;
	size_t			buff_size;
	size_t			index;
	char			**files;

	index = 0;
	buff_size = 10;
	files = malloc(buff_size * sizeof(char*));
	if (!files)
		return NULL; // malloc error
	bzero(files, buff_size * sizeof(char*));
	if (!*path)
		*path = home_dir();
	if (!(dir = opendir(*path)))
		return (NULL); // TODO
	while ((file = readdir(dir)))
	{
		if (!strcmp(".", file->d_name))
			continue ;
		if (index >= buff_size)
		{
			files = realloc(files, buff_size * 2 * sizeof(char*));
			if (!files)
				return NULL; // malloc error
			buff_size *= 2;
		}
		files[index] = file->d_name;
		index += 1;
	}
	print_files(files, index);
	*len = index;
	qsort(files, index, sizeof(char*), &strcmp_wrapper);
	return files;
}

static void	fill_surface(SDL_Surface *surface, char **list, size_t len,
	int height, t_selector_settings settings)
{
	size_t		index;
	SDL_Surface	*file_name;
	int 		char_size;
	size_t		max_len;
	size_t		text_len;

	char_size = get_char_size(g_font);
	max_len = surface->w - settings.padding / char_size;
	index = 0;
	while (index < len)
	{
		text_len = strlen(list[index]);
		if (text_len > 3 && max_len < text_len)
		{
			// TODO new string, do not chnage original string
			list[index][max_len - 3] = '.';
			list[index][max_len - 2] = '.';
			list[index][max_len - 1] = '.';
			list[index][max_len] = '\0';
		}
		file_name = TTF_RenderText_Solid(g_font, list[index], settings.text_color);
		SDL_BlitSurface(file_name, NULL, surface, &(SDL_Rect){0, height * index, 0, 0});
		index += 1;
	}
	return ;
}


static void	event_handler(SDL_Event event, void *data)
{
	e_file_selector_action *action;

	action = (e_file_selector_action*)data;
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_DOWN)
			*action = DOWN;
		else if (event.key.keysym.sym == SDLK_UP)
			*action = UP;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (VALIDATE_KEY(event.key.keysym.sym))
			*action = ENTER;
		else if (event.key.keysym.sym == SDLK_BACKSPACE)
			*action = PREVIOUS;
		else if (event.key.keysym.sym == SDLK_ESCAPE)
			*action = ESCAPE;
	}
	return ;
}

static void	display_it(SDL_Surface *files_list, t_selector_settings settings,
	size_t index, size_t top_index, int height)
{
	SDL_Rect				tmp_rect;

	tmp_rect = (SDL_Rect){settings.position.x, settings.position.y + height,
		settings.position.w, settings.position.h - height};
	SDL_FillRect(settings.father, &tmp_rect, settings.background_color);
	tmp_rect = (SDL_Rect){settings.position.x,
		(index - top_index) * height + settings.position.y + height,
		settings.position.w - settings.padding, height};
	SDL_FillRect(settings.father, &tmp_rect, settings.selector_color);
	tmp_rect = (SDL_Rect){settings.position.x, settings.position.y + height,
		settings.position.w, settings.position.h - height};
	SDL_BlitSurface(files_list, &(SDL_Rect){0, top_index * height, files_list->w,
		settings.position.h - height}, settings.father, &tmp_rect);
	SDL_UpdateWindowSurface(g_window);
	return ;
}

static void	display_path(t_selector_settings settings, char *path, int height)
{
	SDL_Surface				*path_surface;

	path_surface = TTF_RenderText_Solid(g_font, path, settings.text_color);
	SDL_FillRect(settings.father, &(SDL_Rect){settings.position.x, settings.position.y,
		settings.position.w, height}, settings.path_background);
	SDL_BlitSurface(path_surface, NULL, settings.father, &(SDL_Rect){settings.position.x,
		settings.position.y, settings.position.w, height});
	SDL_FreeSurface(path_surface);
}


char *file_selector(char *path, t_selector_settings settings)
{
	size_t					len; // number of file in the directory, length of files
	int						height; // height of one line
	char					**files; // array of the files names
	SDL_Surface				*files_list; // Surface with the files names
	e_file_selector_action	action; // last action trigered by the user
	size_t					index; // Index of the selection cursor
	size_t					top_index; // Index of the first file in the top
	size_t					files_display; // Number of file that can be display on the same time


	files = get_files(&path, &len);
	index = 0;
	top_index = 0;
	if (!files)
		return NULL; // TODO
	height = TTF_FontHeight(g_font) + settings.padding;
	files_list = SDL_CreateRGBSurface(0, settings.position.w - settings.padding,
		height * len, 32, RMASK, GMASK, BMASK, AMASK);
	fill_surface(files_list, files, len, height, settings);
	files_display = settings.position.h / height;
	display_path(settings, path, height);
	display_it(files_list, settings, index, top_index, height);
	while (1)
	{
		action = NO_EVENT;
		event(&event_handler, &action);
		if (action != NO_EVENT)
		{
			if (action == ESCAPE)
				return free_everything(files_list, files, NULL, path, settings);
			if (action == ENTER)
				return free_everything(files_list, files, files[index], path, settings);
			if (action == UP && index > 0)
			{
				index -= 1;
				if (index < top_index)
				top_index -= 1;
			}
			if (action == DOWN && index + 1 < len)
			{
				index += 1;
				if (index >= files_display + top_index - 1)
					top_index += 1;
			}
			display_it(files_list, settings, index, top_index, height);
		}
	}
	return NULL;
}
