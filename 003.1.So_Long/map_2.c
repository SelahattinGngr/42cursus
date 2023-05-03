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