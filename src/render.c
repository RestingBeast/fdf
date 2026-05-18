/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:25:40 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/05/18 17:25:42 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_total(t_line *l)
{
	if (l->dx > l->dy)
		return (l->dx);
	return (l->dy);
}

static void	step_line(t_line *l, t_point *a)
{
	int	e2;

	e2 = 2 * l->err;
	if (e2 > -l->dy)
	{
		l->err -= l->dy;
		a->x += l->sx;
	}
	if (e2 < l->dx)
	{
		l->err += l->dx;
		a->y += l->sy;
	}
}

static void	draw_line(t_data *data, t_point a, t_point b)
{
	t_line	l;
	int		steps;
	int		total;

	init_line(&l, a, b);
	total = get_total(&l);
	steps = 0;
	while (1)
	{
		my_mlx_pixel_put(data->image, a.x, a.y,
			lerp_color(a.color, b.color, (float)steps / (total + 1)));
		if (a.x == b.x && a.y == b.y)
			break ;
		step_line(&l, &a);
		steps++;
	}
}

static void	draw_connections(t_data *data, int x, int y)
{
	t_point	cur;
	t_point	next;

	cur = project(data, x, y);
	if (x + 1 < data->map->width)
	{
		next = project(data, x + 1, y);
		draw_line(data, cur, next);
	}
	if (y + 1 < data->map->height)
	{
		next = project(data, x, y + 1);
		draw_line(data, cur, next);
	}
}

void	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			draw_connections(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}
