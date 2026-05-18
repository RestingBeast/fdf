#include "fdf.h"

static void    cleanup(t_data *data)
{
    if (data->image)
    {
        mlx_destroy_image(data->mlx, data->image->img);
        free(data->image);
    }
    if (data->map)
    {
        free_2d_arr((void **)data->map->z_indices);
        free_2d_arr((void **)data->map->colors);
    }
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
}

static int close_handler(t_data *data)
{
    cleanup(data);
    exit(0);
}

static int key_handler(int keycode, t_data *data)
{
    if (keycode == 65307)  // ESC on Linux
    {
        cleanup(data);
        exit(0);
    }
    return (0);
}

void init_window(t_data *data, int width, int height, char *title)
{
    data->image = init_image(data->mlx, width, height);
    if (!data->image)
    {
        free(data->mlx);
        exit(1);
    }
    data->win = mlx_new_window(data->mlx, width, height, title);
    mlx_key_hook(data->win, key_handler, data);
    mlx_hook(data->win, 17, 0, close_handler, data); 
}
