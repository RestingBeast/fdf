#ifndef FDF_H
# define FDF_H
# include "ft_printf.h"
# include "mlx.h"

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_data
{
    void    *mlx;
    void    *win;
	t_img	*image;
}   t_data;

void	my_mlx_pixel_put(t_img *image, int x, int y, int color);
t_img	*init_image(void *mlx, int width, int height);
void	init_window(t_data *data, int widht, int height, char *title);

#endif
