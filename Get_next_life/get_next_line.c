/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:14:00 by jelusine          #+#    #+#             */
/*   Updated: 2018/06/23 22:51:20 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

static	t_list	*ft_new_lst(size_t fd)
{
	static t_list	*save = NULL;
	t_list			*tmp;

	tmp = save;
	while (tmp && tmp->content_size != fd)
		tmp = tmp->next;
	if (!tmp)
	{
		ft_lstadd(&save, tmp = ft_lstnew("", 1));
		tmp->content_size = fd;
	}
	return (tmp);
}

static	int		last_one(char **str, char **save, int k)
{
	if (!(*str = ft_strsub(*save, 0, k)))
		return (-1);
	ft_strcpy(*save, ((ft_strcmp(*save + k, "")) ? *save + k + 1 : ""));
	return (1);
}

static char		*ft_strjoin_free(char **s1, char *s2)
{
	char		*str;
	const int	len1 = ft_strlen(*s1);

	if (!(*s1 && s2) ||
			!(str = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(str, *s1);
	ft_strdel(s1);
	ft_strcpy(str + len1, s2);
	return (str);
}

int				get_next_line(const int fd, char **str)
{
	int			indk[3];
	char		*buff;
	t_list		*tmp;

	tmp = ft_new_lst(fd);
	if ((indk[1] = read(fd, tmp->content, 0)) > -1 &&
			(indk[0] = ft_charcmpstr('\n', tmp->content)) == -1)
	{
		indk[0] = ft_strlen(tmp->content) + indk[1]--;
		if (!(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		while (indk[1]++ == -1 && (indk[2] = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[indk[2]] = '\0';
			indk[0] += indk[2];
			if (!(tmp->content = ft_strjoin_free((char **)&tmp->content, buff)))
				return (-1);
			if ((indk[1] = ft_charcmpstr('\n', buff)) != -1)
				indk[0] -= indk[2] - indk[1];
		}
		ft_strdel(&buff);
	}
	if (tmp->content && ft_strcmp(tmp->content, "") != 0)
		return (last_one(str, (char **)&tmp->content, indk[0]));
	return (indk[1]);
}
