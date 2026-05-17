#include "fdf.h"

t_img *init_image(void *mlx, int width, int height)
{
	t_img	*image;

	image = malloc(sizeof(t_img));
	if (!image)
		return (NULL);
    image->img = mlx_new_image(mlx, width, height);
    image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
        &image->line_length, &image->endian);
	return (image);
}

void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
