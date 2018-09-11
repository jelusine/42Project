/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:52:49 by jelusine          #+#    #+#             */
/*   Updated: 2018/09/11 03:11:12 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	ft_tracecrox(int pnt[2], void *ptr, int color, int bold)
{
	int				i;
	const int		born = (bold - 1) / 2;
	const t_test	*test = ptr;

	i = -1;
	while (++i < bold)
	{
		mlx_pixel_put(test->mlx_ptr, test->win_ptr,
				pnt[0] - born + i, pnt[1], color);
		mlx_pixel_put(test->mlx_ptr, test->win_ptr,
				pnt[0], pnt[1] - born + i, color);
	}
}

int		ft_polygone(int key, int x, int y, void *ptr)
{
	const int	pnt[2] = {x, y};
	static int	org[2][2];

	if (key == 3)
	{
		org[0][0] = x;
		org[0][1] = y;
		org[1][0] = x;
		org[1][1] = y;
		ft_tracecrox(org[0], ptr, 0x00ffff, 7);
		return (1);
	}
	else if (key == 1)
	{
		trace_ligne(org[1], pnt, ptr, -1);
		org[1][0] = x;
		org[1][1] = y;
		return (1);
	}
	else if (key == 2)
		trace_ligne(org[0], org[1], ptr, -1);
	return (0);
}

void	ft_paintashier(int key, const int coor[2], t_test *test, int *k)
{
	int				pb[2];
	static int		pa[2] = {-1, -1};

	if (key == 3)
		*k = 3;
	else if (key == 2 && (*k == -1 || *k == 2))
		*k = 1 - *k;
	else if (((key == 5 && test->bold > 0) || (key == 4 && test->bold < 51)))
		test->bold += 9 - 2 * key;
	if (*k == 2)
	{
		if (key == 2)
		{
			pa[0] = coor[0];
			pa[1] = coor[1];
			ft_tracecrox(pa, test, 0xffff00, 7);
		}
		else if (key == 1)
			if (pa[0] > 0 && coor[1] > 0 && (pb[0] = coor[0])
					&& (pb[1] = coor[1]))
				trace_ligne(pa, pb, test, -1);
	}
	else if (*k == 3 && !ft_polygone(key, coor[0], coor[1], test))
		*k = -1;
}

int		ft_change_color(long *col, int i)
{
	int			tmp;
	static int	pui[2] = {1, 1};
	static int	neg[2] = {1, 1};

	if (*col % 0xffffff != 0)
	{
		if ((tmp = (*col / (int)pow(256, pui[i])) % 256) % 255 == 0)
			neg[i] = 1 - (2 * tmp / 255);
		*col += CHCOL * neg[i] * pow(256, pui[i]);
		if ((*col / (int)pow(256, pui[i])) % 255 == 0 && ((pui[i] += 1) || 1))
			if ((pui[i] + 1) % 4 == 0)
				pui[i] = (3 - pui[i]) / 2;
		if (*col == 0xff3300)
			*col = 0;
	}
	else
	{
		if (*col == 0)
			*col = 0xffffff;
		else
			*col = 0xff3300;
	}
	return (1);
}

int		pseudo_snake(int key, void *ptr)
{
	int				cor[2];
	float			n;
	static int		k = 1;
	static int		coor[2] = {WIDTH / 2, HEIGHT / 2};
	t_test			*test;

	test = ptr;
	n = (key == 49 ? 1.5 : 0.5);
	if (key == 6)
		return (ft_change_color(&TIP.col[0], 0));
	if (key == 12)
		k *= -1;
	else if (key == 124 || key == 123 || key == 125 || key == 126)
		coor[(key < 125 ? 0 : 1)] += (key < 125 ? 2 * key - 247
				: -2 * key + 251) * PIX;
	if (k < 0)
		ft_change_color(&TIP.col[0], 0);
	cor[1] = -1;
	while (++cor[1] < 2 * PIX * n && (cor[0] = -1))
		while (++cor[0] < 2 * PIX * n)
			mlx_pixel_put(test->mlx_ptr, test->win_ptr,
			coor[0] + cor[0] - PIX * n, coor[1] + cor[1] - PIX * n, TIP.col[0]);
	return (0);
}
