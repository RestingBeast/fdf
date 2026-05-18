/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 02:52:40 by kkhant-z          #+#    #+#             */
/*   Updated: 2026-05-18 02:52:40 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_handler(t_data *data)
{
	cleanup(data);
	exit(0);
}

static int	key_handler(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		close_handler(data);
	return (0);
}

static int	expose_handler(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	return (0);
}

void	init_window(t_data *data, int width, int height, char *title)
{
	data->image = init_image(data->mlx, width, height);
	data->win = mlx_new_window(data->mlx, width, height, title);
	if (!data->win)
		fatal_error("mlx_new_window failed");
	mlx_key_hook(data->win, key_handler, data);
	mlx_hook(data->win, 17, 0, close_handler, data);
	mlx_hook(data->win, 12, 0, expose_handler, data);
}
