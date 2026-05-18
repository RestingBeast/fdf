#include "fdf.h"

static void	set_width(t_map *map, char *line)
{
	char	**arr;
	int		count;

	count = 0;
	arr = ft_split(line, ' ');
	while (arr[count] != NULL)
		count++;
	map->width = count;
	free_2d_arr((void **)arr);
}

void    set_width_and_height(t_map *map, char *mapFile)
{
    int     fd;
    char    *line;

    fd = open(mapFile, O_RDONLY);
    if (fd == -1)
        exit(1);
	map->height = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
		if (map->height == 0)
			set_width(map, line);
        free(line);
        line = get_next_line(fd);
		map->height++;
    }
    free(line);
	close(fd);
}

void	map_error(t_map *map, char **content)
{
	int	i;

	free_2d_arr((void **)map->z_indices);
	free_2d_arr((void **)map->colors);
	if (content)
	{
		i =0;
		while (content[i] != NULL)
			free(content[i++]);
		free(content);
	}
	exit(1);
}

int	extract_color(t_map *map, char **content, char *color)
{
	int	res;

    if (!color)
        return (0xffffff);
    color++;
    if (color[0] != '0' || (color[1] != 'x' && color[1] != 'X'))
        map_error(map, content);
	res = 0;
    color += 2;
	while (*color != '\0')
	{
		if (*color >= '0' && *color <= '9')
            res = (res * 16) + (*color - '0');
        else if (*color >= 'a' && *color <= 'f')
            res = (res * 16) + (*color - 'a' + 10);
        else if (*color >= 'A' && *color <= 'F')
            res = (res * 16) + (*color - 'A' + 10);
        else
            map_error(map, content);
		color++;
	}
	return (res);
}

char    *extract_z_index(char *str)
{
    int count;

    count = 0;
    while (str[count] != '\0' && str[count] != ',')
        count++;
    return (ft_substr(str, 0, count));
}
