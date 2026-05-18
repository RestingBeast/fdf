#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include "ft_printf.h"
# include "mlx.h"
# include "get_next_line.h"

typedef struct s_map
{
	int				width;
	int				height;
	int				**z_indices;
	int				**colors;
}	t_map;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
    void    *mlx;
    void    *win;
	t_img	*image;
	t_map	*map;
}   t_data;

void	my_mlx_pixel_put(t_img *image, int x, int y, int color);
t_img	*init_image(void *mlx, int width, int height);
void	init_window(t_data *data, int widht, int height, char *title);
// map.c
void    init_map(t_map *map, char *mapFile);
void    parse_map(t_map *map, char *mapFile);
// map_utils.c
void    set_width_and_height(t_map *map, char *mapFile);
void    set_width_and_height(t_map *map, char *mapFile);
void	map_error(t_map *map, char **content);
int		extract_color(t_map *map, char **content, char *color);
char    *extract_z_index(char *str);
// utils.c
void    free_2d_arr(void **arr);

#endif
