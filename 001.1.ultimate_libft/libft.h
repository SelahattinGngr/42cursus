/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:16:20 by segungor          #+#    #+#             */
/*   Updated: 2022/12/22 22:16:24 by segungor         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 50

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// get next line utils
char	*get_next_line(int fd);
char	*get_new_line(char *buffer);
char	*first_line(int fd, char *buffer);
char	*get_new_buffer(char *buffer);
char	*ftgnl_strjoin(char *s1, char *s2);
int		find_nl_char(char *buffer);
size_t	ftgnl_strlen(char *buf);

// ft_printf utils
int	    ft_printf(const char *str, ...);
int	ftp_putchar(char c);
int	ftp_putstr(char *str);
int	ftp_itoa_base(unsigned long long nbr, int base, char *str, int mod);
int	ftp_check_format(va_list args, char format);

int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_tolower(int x);
int		ft_toupper(int x);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_lstsize(t_list *lst);

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);

char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *str1, const char *str2, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strchr(const char *s, int c);

void	*ft_memchr(const void *str1, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));

#endif
