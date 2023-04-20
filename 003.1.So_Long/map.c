#include "so_long.h"

// map uzantisini kontrol ediyor
void    ber_control(char *map_name)
{
    int arg_len;

    arg_len = ft_strlen(map_name);
    if (map_name[arg_len - 1] != 'r' || map_name[arg_len - 2] != 'e'
        || map_name[arg_len - 3] != 'b' || map_name[arg_len - 4] != '.')
        err_msg("map .ber uzantisina sahip olmali krdsm");
}
// mapin varligini kontrol ediyor
void    tmp_control(char *map_name)
{
    int fd;
    fd = open(map_name, O_RDONLY);
    if (fd < 0)
        err_msg("boyle bir map yok krdsm");
}

// mapin var olup olmadigini ve .ber uzantisinin olup olmadigini bakiyoruz
void    map_control(char *map_name, t_game *data)
{
    ber_control(map_name);
    data->maplocation = ft_strjoin("map/",map_name);
    tmp_control(data->maplocation);
    // printf("%s",data->maplocation);
}