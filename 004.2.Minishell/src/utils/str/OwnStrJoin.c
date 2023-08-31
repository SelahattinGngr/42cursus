#include "../../../Include/minishell.h"

/*
	gonderilen dst dizisine src'yi ekler.
	Eger dst'nin ici bos ise sadece src ile yaratilir.
	İslemlerden sonra eger onceden bir dst degeri var ise bu freelenir
	ve ardindan yeni olusturulan dizi dst'ye atanir.
*/
void	own_strjoin(char **dst, char *src)
{
	char	*ptr;
	char	*holder_ptr;
	char	*holder_dst;
	size_t	len;

	if (!*dst && !src)
		return ;
	len = ft_strlen(*dst) + ft_strlen(src);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	ptr[len] = 0;
	holder_ptr = ptr;
	holder_dst = *dst;
	while (holder_dst && *holder_dst)
		*(holder_ptr++) = *(holder_dst++);
	while (src && *src)
		*(holder_ptr++) = *(src++);
	if (*dst)
		free(*dst);
	*dst = ptr;
}
