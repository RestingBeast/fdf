/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 02:52:33 by kkhant-z          #+#    #+#             */
/*   Updated: 2026-05-18 02:52:33 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_2d_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

void	cleanup(t_data *data)
{
	if (data->map)
	{
		free_2d_arr((void **)data->map->z_indices);
		free_2d_arr((void **)data->map->colors);
	}
	if (data->image)
	{
		mlx_destroy_image(data->mlx, data->image->img);
		free(data->image);
	}
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	fatal_error(char *msg)
{
	perror(msg);
	exit(1);
}
