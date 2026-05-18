#include "fdf.h"

static int	**allocate_2d_arr(int height, int width)
{
	int	**res;
	int	*arr;
	int	i;

	res = malloc((height + 1) * sizeof(int *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < height)
	{
		res[i] = malloc(width * sizeof(int));
		if (!res[i])
		{
			while (i--)
				free(res[i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void    init_map(t_map *map, char *mapFile)
{
    int **z_indices;
    int **colors;

	set_width_and_height(map, mapFile);
	z_indices = allocate_2d_arr(map->height, map->width);
    if (!z_indices)
        exit(1);
    colors = allocate_2d_arr(map->height, map->width);
    if (!colors)
    {
        free_2d_arr((void **)z_indices);
        exit(1);
    }
    map->z_indices = z_indices;
    map->colors = colors;
	map->height = 0;
}

static void	parse_z_and_color(t_map *map, char **content, int curr_i)
{
	int		i;
	char	*comma;
	char	*z_index;

	comma = ft_strchr(content[curr_i], ',');
	if (comma && ft_strlen(comma) == 1)
		map_error(map, content);
	if (comma && content[curr_i][0] == ',')
		map_error(map, content);
    i = 0;
	if (i == 0 && (content[curr_i][i] == '-' || content[curr_i][i] == '+'))
    	i++;
    while (content[curr_i][i] != '\0' && content[curr_i][i] != ',' )
    {
        if (!ft_isdigit(content[curr_i][i]))
            map_error(map, content);
        i++;
    }
	z_index = extract_z_index(content[curr_i]);
	if (!z_index)
		map_error(map, content);
	map->z_indices[map->height][curr_i] = ft_atoi(z_index);
	map->colors[map->height][curr_i] = extract_color(map, content, comma);
	free(z_index);
}

static void    process_line(t_map *map, char **content)
{
    int i;

    i = 0;
    while (content[i] != NULL){	
        parse_z_and_color(map, content, i);
		i++;
		if (i > map->width)
			map_error(map, content);
    }
	map->height += 1;
}

void    parse_map(t_map *map, char *mapFile)
{
    int     fd;
    char    *line;
	char	**content;

    fd = open(mapFile, O_RDONLY);
    if (fd == -1)
        exit(1);
    line = get_next_line(fd);
    while (line != NULL)
    {
		line[ft_strlen(line) - 1] = '\0';
		content = ft_split(line, ' ');
		process_line(map, content);
		free_2d_arr((void **)content);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
	close(fd);
}
