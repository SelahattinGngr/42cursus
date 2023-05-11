#include "libft.h"

size_t	ftgnl_strlen(char *buf)
{
    size_t	i;

    i = 0;
    if (!buf)
        return (0);
    while (buf[i])
        i++;
    return (i);
}