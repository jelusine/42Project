/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 09:05:56 by jelusine          #+#    #+#             */
/*   Updated: 2018/07/08 12:41:14 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

t_point		**ft_fill(t_point **tab, t_list *lst, int lenx)
{
	int			y;
	int			x;
	char		**tmpnb;
	t_list		*tmp;

	tmp = lst;
	y = -1;
	while (tmp && ++y >= 0)
	{
		tmpnb = ft_strsplit(tmp->content, ' ');
		ft_strdel((char **)&tmp->content);
		tmp = tmp->next;
		if (!(tab[y] = (t_point *)malloc(sizeof(t_point) * (lenx))))
			return (NULL);
		x = -1;
		while (++x < lenx)
		{
			tab[y][x].y = y;
			tab[y][x].x = x;
			tab[y][x].z = (tmpnb[x] ? ft_atoi(tmpnb[x]) : 0);
			if (tmpnb[x])
				ft_strdel(&tmpnb[x]);
		}
	}
	return (tab);
}

t_gridpnt	*ft_osef(t_list *lst, int lenx, int leny)
{
	t_gridpnt	*grid;
	t_point		**tab;

	if (!(grid = (t_gridpnt *)malloc(sizeof(t_gridpnt))))
		return (NULL);
	grid->leny = leny;
	grid->lenx = lenx;
	if (!(tab = (t_point **)malloc(sizeof(t_point *) * grid->leny)))
		return (NULL);
	grid->cstc = CST2;
	grid->zc = 0;
	if (!(grid->tab = ft_fill(tab, lst, grid->lenx)))
		return (NULL);
	return (grid);
}

int			compt_ward(char *str)
{
	int		i;
	int		nw;

	i = 0;
	nw = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (str[i] != ' ' && str[i])
		{
			i++;
			if (str[i] == ' ' || !str[i])
				nw++;
		}
	}
	return (nw);
}

t_gridpnt	*ft_parser(char *path)
{
	int			fd;
	int			n;
	char		*line;
	t_list		*save;
	t_pointa	len;

	save = NULL;
	len.x = 0;
	len.y = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	while ((n = get_next_line(fd, &line)) > 0)
	{
		len.y++;
		len.x = ft_max(len.x, compt_ward(line));
		ft_lstaddend(&save, ft_lstnew(line, ft_strlen(line) + 1));
		ft_strdel(&line);
	}
	close(fd);
	if (n >= 0)
		return (ft_osef(save, len.x, len.y));
	return (NULL);
}
