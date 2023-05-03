#include "so_long.h"

void map_bug(t_game *data)
{
    int P;
    int E;
    int i;
    int j;

    P = 0;
    E = 0;
    i = -1;
    while (++i < data->map_height)
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (data->map[i][j] == 'P')
                P++;
            if (data->map[i][j] == 'E')
                E++;
        }
    }
    if (P > 1 || P == 0 || E > 1 || E == 0 || data->collectables == 0)
        err_msg("eksik ve ya fazla seyler var amigo");
}

static int	recur_func(int **int_map, t_game *data, int x, int y)
{
    if (data->map[y][x] == 'E' || data->map[y][x] == 'C')
        data->read_count++;
    if (data->map[y][x + 1] != '1' && int_map[y][x + 1] < 1)
    {
        int_map[y][x + 1] = int_map[y][x] + 1;
        recur_func(int_map, data, x + 1, y);
    }
    if (data->map[y + 1][x] != '1' && int_map[y + 1][x] < 1)
    {
        int_map[y + 1][x] = int_map[y][x] + 1;
        recur_func(int_map, data, x, y + 1);
    }
    if (data->map[y][x - 1] != '1' && int_map[y][x - 1] < 1)
    {
        int_map[y][x - 1] = int_map[y][x] + 1;
        recur_func(int_map, data, x - 1, y);
    }
    if (data->map[y - 1][x] != '1' && int_map[y - 1][x] < 1)
    {
        int_map[y - 1][x] = int_map[y][x] + 1;
        recur_func(int_map, data, x, y - 1);
    }
    return (0);
}

static void	int_map_free(int **int_map, t_game *data)
{
    int	i;

    i = 0;
    while (i < data->map_height)
    {
        free(int_map[i]);
        i++;
    }
    free(int_map);
}

void	placeholder(t_game *data, int x, int y)
{
    int	**int_map;
    int	i;
    int	j;

    i = 0;
    j = 0;
    int_map = (int **)malloc(sizeof(int *) * data->map_height);
    while (i < data->map_height)
    {
        int_map[i] = (int *)malloc(sizeof(int) * data->map_width);
        j = 0;
        while (j < data->map_width)
        {
            int_map[i][j] = 0;
            j++;
        }
        i++;
    }
    int_map[y][x] = 1;
    data->read_count = 0;
    recur_func(int_map, data, x, y);
    if (data->read_count != data->collectables + 1)
        err_msg(">>>The map is wrong");
    int_map_free(int_map, data);
}