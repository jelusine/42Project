/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 09:05:56 by jelusine          #+#    #+#             */
/*   Updated: 2018/09/09 06:55:24 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int			ft_ref(void *ptr, t_point *p)
{
	t_test *test;

	test = ptr;
	if (!p && TIP.ref.x < 0)
		TIP.ref.y = ++TIP.ref.x;
	else if (TIP.ref.x < 0 && p && !p->z)
	{
		TIP.ref.x = p->x;
		TIP.ref.y = p->y;
	}
	return (0);
}

t_point		**ft_fill(t_point **tab, t_list *lst, int lenx, t_test *test)
{
	t_pointa	p;
	t_list		*tmp;
	char		**tmpnb;

	tmp = lst;
	p.y = -1;
	while (tmp && ++p.y >= 0 && (lst = tmp))
	{
		tmpnb = ft_strsplit(tmp->content, ' ');
		tmp = tmp->next;
		ft_lstdelone(&lst, &del);
		if (!(tab[p.y] = (t_point *)malloc(sizeof(t_point) * (lenx))))
			return (NULL);
		p.x = -1;
		while (++p.x < lenx
			&& (tab[p.y][p.x].y = p.y) > -1
			&& (tab[p.y][p.x].x = p.x) > -1
			&& ((tab[p.y][p.x].z = (tmpnb[p.x] ? ft_atoi(tmpnb[p.x]) : 0)) || 1)
			&& !ft_ref(test, &tab[p.y][p.x]))
			if (tmpnb[p.x])
				ft_strdel(&tmpnb[p.x]);
		free(tmpnb);
	}
	ft_ref(test, NULL);
	return (tab);
}

t_gridpnt	*ft_osef(t_list *lst, int lenx, int leny, t_test *test)
{
	int			i;
	t_point		**tab;
	t_gridpnt	*grid;

	if (!(grid = (t_gridpnt *)malloc(sizeof(t_gridpnt))))
		return (NULL);
	grid->leny = leny;
	grid->lenx = lenx;
	if (!(tab = (t_point **)malloc(sizeof(t_point *) * grid->leny)))
		return (NULL);
	grid->cstc = CST2;
	grid->zc = 0;
	if (!(grid->tab = ft_fill(tab, lst, grid->lenx, test)))
		return (NULL);
	i = 0;
	test->pzoom = leny * lenx;
	while (test->pzoom >= 1)
	{
		test->pzoom /= 10;
		i++;
	}
	test->pzoom = (i >= 5 ? 1 : 0);
	test->lola[0] = WIDTH;
	test->lola[1] = HEIGHT;
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

t_gridpnt	*ft_parser(char *path, t_test *test)
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
	test->lim = 5711 * (pow(len.x * len.y, -0.478)) * 0.5;
	test->limmin = -1385 * (pow(len.x * len.y, -0.566)) * 0.7;
	if (n >= 0)
		return (ft_osef(save, len.x, len.y, test));
	return (NULL);
}
