#include "fdf.h"

int main(int argc, char **argv)
{
    t_data  data;
	t_map	map;

	if (argc != 2)
		return (1);
	init_map(&map, argv[1]);
	parse_map(&map, argv[1]);
    data.mlx = mlx_init();
	data.map = &map;
    init_window(&data, 700, 700, "Hello, World");
	int x = 0;
	while (x < 300)
	{
		int y = 0;
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
