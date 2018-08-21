/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:18:28 by jelusine          #+#    #+#             */
/*   Updated: 2018/08/21 03:13:18 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 8
# define NL ft_putchar('\n');
# define TEST0 ft_putendl("Test");
# define TEST1 ft_color("**Test1**\n", "g");
# define TEST2 ft_color("//Test2\\\\\n", "+r");
# define TEST3 ft_color("++Test3++\n", "c");
# define TEST4 ft_color("\\\\Test4//\n", "+y");
# define TEST5 ft_color("--Test5--\n", "p");

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
**  || PARTIE 1 ||
*/

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *str);
void			ft_bzero(void *str, size_t n);
void			ft_memdel(void **huh);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
char			*ft_strdup(const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);

/*
**  || PARTIE 2 ||
*/

int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(const char *str);
void			ft_putstr_fd(const char *str, int fd);
void			ft_putendl(const char *str);
void			ft_putendl_fd(const char *str, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_strclr(char *str);
void			ft_strdel(char **str);
void			ft_striter(char *str, void (*f)(char *));
void			ft_striteri(char *str, void (*f)(unsigned int, char *));
void			*ft_memalloc(size_t len);
char			*ft_itoa(int nb);
char			*ft_strnew(size_t len);
char			*ft_strtrim(const char *src);
char			**ft_strsplit(const char *str, char c);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strsub(const char *src, unsigned int deb, size_t len);
char			*ft_strmap(const char *src, char (*f)(char));
char			*ft_strmapi(const char *src, char (*f)(unsigned int, char));

/*
**  || PARTIE BONUS ||
*/

void			ft_lstadd(t_list **alst, t_list *newele);
void			ft_lstiter(t_list *lst, void (*f)(t_list *));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));
t_list			*ft_lstnew(const void *content, size_t len);

/*
**  || PARTIE ADDITIONELLE ||
*/

long			ft_abs(int n);
int				ft_min(int x, int y);
int				ft_max(int x, int y);
int				ft_charcmpstr(char c, const char *str);
int				ft_analyse_base(const char *str);
int				ft_atoi_base(const char *str, const char *base);
int				get_next_line(int fd, char **line);
int				ft_errormsg(char const *str);
int				ft_swap(int *a, int *b);
char			*ft_itoa_base(int nb, int base);
char			**ft_split(const char *str, char *kwords);
void			ft_putnbr_base(int nbr, const char *base);
void			ft_color(const char *str, const char *color);
void			ft_charcolor(char c, const char *color);
void			ft_lstaddend(t_list **alst, t_list *newele);
void			ft_lst_remove_if(t_list **begin, void *data,
								int (*cmp)(), void (*del)(void *, size_t));
void			ft_lst_remove_if_size(t_list **begin, size_t data,
										void (*del)(void *, size_t));

#endif
