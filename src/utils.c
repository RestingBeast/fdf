#include "fdf.h"

void    free_2d_arr(void **arr)
{
    int i = 0;
    while (arr[i] != NULL)
        free(arr[i++]);
    free(arr);
}
