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

int	lerp_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((c1 >> 16 & 0xFF) * (1 - t)) + ((c2 >> 16 & 0xFF) * t));
	g = (int)(((c1 >> 8 & 0xFF) * (1 - t)) + ((c2 >> 8 & 0xFF) * t));
	b = (int)(((c1 & 0xFF) * (1 - t)) + ((c2 & 0xFF) * t));
	return (r << 16 | g << 8 | b);
}

t_point	project(t_data *data, int x, int y)
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

void	init_line(t_line *l, t_point a, t_point b)
{
	l->dx = abs(b.x - a.x);
	l->dy = abs(b.y - a.y);
	if (a.x < b.x)
		l->sx = 1;
	else
		l->sx = -1;
	if (a.y < b.y)
		l->sy = 1;
	else
		l->sy = -1;
	l->err = l->dx - l->dy;
}
