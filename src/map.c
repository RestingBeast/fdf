/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 05:32:48 by kkhant-z          #+#    #+#             */
/*   Updated: 2026-05-18 05:32:48 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	**allocate_2d_arr(int height, int width)
{
	int	**res;
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

void	init_map(t_map *map, char *mapfile)
{
	int	**z_indices;
	int	**colors;

	set_width_and_height(map, mapfile);
	z_indices = allocate_2d_arr(map->height, map->width);
	if (!z_indices)
		fatal_error("malloc failed: z_indices");
	colors = allocate_2d_arr(map->height, map->width);
	if (!colors)
	{
		free_2d_arr((void **)z_indices);
		fatal_error("malloc failed: colors");
	}
	map->z_indices = z_indices;
	map->colors = colors;
	map->height = 0;
}

static void	parse_z_and_color(t_map *map, char **content, int curr_i)
{
	char	*comma;
	char	*z_index;
	int		i;

	comma = ft_strchr(content[curr_i], ',');
	if (comma && (ft_strlen(comma) == 1 || content[curr_i][0] == ','))
		map_error(map, content);
	i = 0;
	if (content[curr_i][i] == '-' || content[curr_i][i] == '+')
		i++;
	while (content[curr_i][i] != '\0' && content[curr_i][i] != ',')
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

static void	process_line(t_map *map, char **content)
{
	int	i;

	i = 0;
	while (content[i] != NULL)
	{
		if (i >= map->width)
			map_error(map, content);
		parse_z_and_color(map, content, i);
		i++;
	}
	if (i != map->width)
		map_error(map, content);
	map->height += 1;
}

void	parse_map(t_map *map, char *mapfile)
{
	int		fd;
	char	*line;
	char	**content;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		fatal_error(mapfile);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\r')
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
