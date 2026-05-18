/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 05:32:25 by kkhant-z          #+#    #+#             */
/*   Updated: 2026-05-18 05:32:25 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	find_z_range(t_map *map)
{
	int	z_min;
	int	z_max;
	int	x;
	int	y;

	z_min = map->z_indices[0][0];
	z_max = map->z_indices[0][0];
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->z_indices[y][x] < z_min)
				z_min = map->z_indices[y][x];
			if (map->z_indices[y][x] > z_max)
				z_max = map->z_indices[y][x];
			x++;
		}
		y++;
	}
	return (z_max - z_min);
}

static float	compute_scale(t_map *map)
{
	float	scale_w;
	float	scale_h;

	// Scale the grid so it fills exactly 70% of the window width/height
	scale_w = (WIN_W * 0.70f) / ((map->width + map->height) * 0.866025f);
	scale_h = (WIN_H * 0.70f) / ((map->width + map->height) * 0.5f);
	if (scale_w < scale_h)
		return (scale_w);
	return (scale_h);
}

static void	init_cam(t_data *data)
{
	t_cam	*cam;
	int		z_range;

	cam = &data->cam;
	cam->scale = compute_scale(data->map);
	z_range = find_z_range(data->map);
	if (z_range == 0)
		cam->z_scale = 1.0f;
	else
		cam->z_scale = (float)WIN_H / (z_range * 4);

	// Corrected Math: Shifts the entire frame left/right/up/down based on the map's asymmetry
	cam->x_off = (WIN_W / 2) - (((data->map->width - data->map->height) * 0.866025f * cam->scale) / 2);
	cam->y_off = (WIN_H / 2) - (((data->map->width + data->map->height) * 0.5f * cam->scale) / 2);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;

	if (argc != 2)
		fatal_error("Usage: ./fdf <map.fdf>");
	init_map(&map, argv[1]);
	parse_map(&map, argv[1]);
	data.map = &map;
	data.mlx = mlx_init();
	if (!data.mlx)
		fatal_error("mlx_init failed");
	init_cam(&data);
	init_window(&data, WIN_W, WIN_H, "FdF");
	render(&data);
	mlx_loop(data.mlx);
	return (0);
}
