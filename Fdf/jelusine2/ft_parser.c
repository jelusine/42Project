/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 09:05:56 by jelusine          #+#    #+#             */
/*   Updated: 2018/10/24 06:29:27 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int			ft_ref(void *ptr, t_point *p, int x, int y)
{
	t_test *test;

	test = ptr;
	if (!p && TIP.ref.x < 0)
		TIP.ref.y = ++TIP.ref.x;
	else if (TIP.ref.x < 0 && p && !p->z)
	{
		TIP.ref.x = x;
		TIP.ref.y = y;
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
		while (tmpnb[++p.x] && ((tab[p.y][p.x].z = ft_atoi(tmpnb[p.x])) || 1)
			&& !ft_ref(test, &tab[p.y][p.x], p.x, p.y))
			ft_strdel(&tmpnb[p.x]);
		while (p.x < lenx && !(tab[p.y][p.x].z = 0))
			ft_ref(test, &tab[p.y][p.x++], p.x, p.y);
		free(tmpnb);
	}
	ft_ref(test, NULL, 0, 0);
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
	grid->cstc = 1;
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
	long	nw;

	i = 0;
	nw = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (ft_charcmpstr(str[i], "0123456789") >= 0
				|| (ft_charcmpstr(str[i], "+-") >= 0
					&& ft_charcmpstr(str[i + 1], "0123456789") >= 0) || !str[i])
		{
			while (str[i] != ' ' && str[i])
				if (str[++i] == ' ' || !str[i])
					if (++nw > 2000)
						return (-1);
		}
		else
			return (-1);
	}
	return (nw);
}

t_gridpnt	*ft_parser(char *path, t_test *test)
{
	int			tfd[2];
	char		*line;
	t_list		*save;
	t_pointa	len;

	save = NULL;
	len.x = 0;
	len.y = 0;
	tfd[0] = 1;
	if ((tfd[1] = open(path, O_RDONLY)) == -1)
		return (NULL);
	while (tfd[0] * len.y >= 0 && (len.z = get_next_line(tfd[1], &line)) > 0)
	{
		len.y = (-1 < len.y && len.y < 2000 ? len.y + 1 : -1);
		len.x = ft_max(len.x,
				(tfd[0] = compt_ward(line)));
		ft_lstaddend(&save, ft_lstnew(line, ft_strlen(line) + 1));
		ft_strdel(&line);
	}
	close(tfd[1]);
	test->lim = 5711 * (pow(len.x * len.y, -0.478)) * 0.5;
	test->limmin = -1385 * (pow(len.x * len.y, -0.566)) * 0.7;
	if (len.z >= 0 && tfd[0] >= 0 && len.x > 0 && len.y > 0)
		return (ft_osef(save, len.x, len.y, test));
	return (NULL);
}
