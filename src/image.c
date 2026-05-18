/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 02:52:01 by kkhant-z          #+#    #+#             */
/*   Updated: 2026-05-18 02:52:01 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	*init_image(void *mlx, int width, int height)
{
	t_img	*image;

	image = malloc(sizeof(t_img));
	if (!image)
		fatal_error("malloc failed: image");
	image->img = mlx_new_image(mlx, width, height);
	if (!image->img)
	{
		free(image);
		fatal_error("mlx_new_image failed");
	}
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return (image);
}

void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = image->addr
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
