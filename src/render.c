/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 05:32:54 by kkhant-z          #+#    #+#             */
/*   Updated: 2026-05-18 05:32:54 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	lerp_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((c1 >> 16 & 0xFF) * (1 - t)) + ((c2 >> 16 & 0xFF) * t));
	g = (int)(((c1 >> 8 & 0xFF) * (1 - t)) + ((c2 >> 8 & 0xFF) * t));
	b = (int)(((c1 & 0xFF) * (1 - t)) + ((c2 & 0xFF) * t));
	return (r << 16 | g << 8 | b);
}

static t_point	project(t_data *data, int x, int y)
{
	t_point	p;
	int		z;
	float	scale;

	scale = data->cam.scale;
	z = data->map->z_indices[y][x] * data->cam.z_scale;
	p.x = (int)((x - y) * cos(0.523599) * scale) + data->cam.x_off;
	p.y = (int)((x + y) * sin(0.523599) * scale - z) + data->cam.y_off;
	p.color = data->map->colors[y][x];
	return (p);
}

static void	init_line(t_line *l, t_point a, t_point b)
{
	l->dx = abs(b.x - a.x);
	l->dy = abs(b.y - a.y);
	l->sx = (a.x < b.x) ? 1 : -1;
	l->sy = (a.y < b.y) ? 1 : -1;
	l->err = l->dx - l->dy;
}

static void	draw_line(t_data *data, t_point a, t_point b)
{
	t_line	l;
	int		steps;
	int		total;
	int		e2;

	init_line(&l, a, b);
	total = (l.dx > l.dy) ? l.dx : l.dy;
	steps = 0;
	while (1)
	{
		my_mlx_pixel_put(data->image, a.x, a.y,
			lerp_color(a.color, b.color, (float)steps / (total + 1)));
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * l.err;
		if (e2 > -l.dy)
		{
			l.err -= l.dy;
			a.x += l.sx;
		}
		if (e2 < l.dx)
		{
			l.err += l.dx;
			a.y += l.sy;
		}
		steps++;
	}
}

void	render(t_data *data)
{
	int		x;
	int		y;
	t_point	cur;
	t_point	next;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
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
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}
