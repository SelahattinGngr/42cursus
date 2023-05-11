#include "libft.h"

char	*ftgnl_strjoin(char *s1, char *s2)
{
    char	*return_str;
    size_t	i;
    size_t	j;

    if (!s1)
    {
        s1 = malloc (sizeof(char));
        s1[0] = '\0';
    }
    if (!s1 || !s2)
        return (NULL);
    return_str = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    i = -1;
    j = 0;
    while (s1[++i])
        return_str[i] = s1[i];
    while (s2[j])
        return_str[i++] = s2[j++];
    return_str[i] = '\0';
    free (s1);
    return (return_str);
}