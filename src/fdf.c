#include "fdf.h"

int main(void)
{
    t_data  data;
	int		x;
	int		y;

    data.mlx = mlx_init();
    init_window(&data, 700, 700, "Hello, World");
	
	x = 0;
	while (x < 300)
	{
		y = 0;
		while (y < 300)
		{
			my_mlx_pixel_put(data.image, 200 + x, 200 + y, 0x2f4f4f);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.image->img, 0, 0);
    mlx_loop(data.mlx);
    return (0);
}
