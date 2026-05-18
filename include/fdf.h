/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-18 02:51:47 by kkhant-z          #+#    #+#             */
/*   Updated: 2026-05-18 02:51:47 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "ft_printf.h"
# include "mlx.h"
# include "get_next_line.h"

# define WIN_W 1280
# define WIN_H 720
# define ESC_KEY 65307

typedef struct s_map
{
	int				width;
	int				height;
	int				**z_indices;
	int				**colors;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_cam
{
	float	scale;
	float	z_scale;
	int		x_off;
	int		y_off;
}	t_cam;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	*image;
	t_map	*map;
	t_cam	cam;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

/* image.c */
t_img	*init_image(void *mlx, int width, int height);
void	my_mlx_pixel_put(t_img *image, int x, int y, int color);

/* window.c */
void	init_window(t_data *data, int width, int height, char *title);

/* map.c */
void	init_map(t_map *map, char *mapfile);
void	parse_map(t_map *map, char *mapfile);

/* map_utils.c */
void	set_width_and_height(t_map *map, char *mapfile);
void	map_error(t_map *map, char **content);
int		extract_color(t_map *map, char **content, char *color);
char	*extract_z_index(char *str);

/* render.c */
void	render(t_data *data);

/* utils.c */
void	free_2d_arr(void **arr);
void	cleanup(t_data *data);
void	fatal_error(char *msg);
void	replace_new_line(char *line);

#endif
