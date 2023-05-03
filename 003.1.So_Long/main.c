#include "so_long.h"

void    err_msg(char *err)
{
    ft_printf("%s",err);
    exit(0);
}

static void *ftt_memset(void *s, int c, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        *(char *)(s + i) = c;
        i++;
    }
    return (s);
}

int exit_point(t_game *data)
{
    int line;

    line = 0;
    if (data->winpointer)
        mlx_destroy_window(data->mlxpointer, data->winpointer);
    free(data->mlxpointer);
    while (line < data->map_height - 1)
        free(data->map[line++]);
    free(data->map);
    exit(0);
}

int main(int argc,char **argv)
{
    t_game data;

    if (argc != 2)
        err_msg("1 tane map gir krdsm");
    ftt_memset(&data, 0, sizeof(t_game));
    map_control(argv[1], &data);
    map_reading(&data);
    map_processing(&data);
    wall_control(&data);
    data.mlxpointer = mlx_init();
    data.winpointer = mlx_new_window(data.mlxpointer, (data.map_width * 40), (data.map_height * 40), "solong");
    images_in_game(&data);
    adding_in_graphics(&data);
    map_bug(&data);
    placeholder(&data, data.x_axis, data.y_axis);
    // basilan tuslarin karsiligini init ile actigimiz alanin icerisine isliyoruz
    // pencerede basilan tuslarin karsiligi basildiginda komut fonksiyonuna aktarilacak
    mlx_key_hook(data.winpointer, controls_working, &data);
    // 17 kapatma eylemidir bu eylem gerceklesirse exit atacak
    mlx_hook(data.winpointer, 17, 0, (void *)exit, 0);
    // butun veriler init ile hazirlanan degiskene verildiginde loopa girer loop icerisinde ne zaman kapatılırsa
        // o zaman loop biter
    mlx_loop(data.mlxpointer);
    return 0;
}