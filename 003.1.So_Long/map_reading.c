#include "so_long.h"

// mapi dataya isler
void    map_processing(t_game *data)
{
    int fd;
    int i;
    int j;
    char *line;

    i = 0;
    data->map = (char **)malloc(sizeof(char *) * data->map_height);
    fd = open(data->maplocation, O_RDONLY);
    while (i < data->map_height)
    {
        j = 0;
        line = get_next_line(fd);
        data->map[i] = (char *)malloc(sizeof(char) * data->map_width);
        if (line == NULL)
            break ;
        while (j < data->map_width)
        {
            data->map[i][j] = line[j];
            j++;
        }
        data->map[i][j] = '\0';
        i++;
        free(line);
    }
    close(fd);
}
// mapin dikdortgen olup olmadıgını kontrol eder
void    map_reading(t_game *data)
{
    int fd;
    int x;
    int y;
    char *line;

    y = 0;
    fd = open(data->maplocation, O_RDONLY);
    line = get_next_line(fd);
    x = (int)ft_strlen(line);
    while (1)
    {
        free(line);
        y++;
        line = get_next_line(fd);
        if (line == NULL)
            break;
    }
    if (line)
        free(line);
    data->map_height = y;
    data->map_width = x - 1;
    if (data->map_height == data->map_width)
        err_msg("watafak amigo map dikdortgen degil");
    close(fd);
}