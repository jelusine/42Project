/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:52:49 by jelusine          #+#    #+#             */
/*   Updated: 2018/08/14 15:57:16 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	ft_tracecrox(int x, int y, void *ptr, int color)
{
	int				i;
	const t_test	*test = ptr;

	i = -1;
	while (++i < 7)
	{
		mlx_pixel_put(test->mlx_ptr, test->win_ptr, x - 3 + i, y, color);
		mlx_pixel_put(test->mlx_ptr, test->win_ptr, x, y - 3 + i, color);
	}
}

int		ft_polygone(int key, int x, int y, void *ptr)
{
	t_pointa		pnt;
	static t_pointa org[2];

	if (key == 3)
	{
		org[0].x = x;
		org[0].y = y;
		org[1].x = x;
		org[1].y = y;
		ft_tracecrox(x, y, ptr, 0xff0000);
		return (1);
	}
	else if (key == 1)
	{
		pnt.x = x;
		pnt.y = y;
		trace_ligne(/*org[1], pnt*/org[1].x, org[1].y, x, y, ptr, 0x00bfff, 1);
		org[1].x = x;
		org[1].y = y;
		return (1);
	}
	else if (key == 2)
		trace_ligne(/*org[0], org[1]*/org[0].x, org[0].y, org[1].x, org[1].y, ptr, 0x00bfff, 1);
	return (0);
}

void	ft_paintashier(int key, int x, int y, void *ptr, int *k)
{
	t_pointa		b;
	const t_test	*test = ptr;
//	static t_pointa	a = {-1, -1, -1};
	static int		xa = -1;
	static int		ya = -1;

	if (key == 3)
		*k = 3;
	if (key == 2 && *k == -1)
		*k = 2;
	if (*k == 2)
	{
		if (key == 2)
		{
			xa = x;
			ya = y;
			ft_tracecrox(xa, ya, ptr, 0xffff00);
		}
		else if (key == 1)
			if (xa > 0 && (b.x = x)
					&& (b.y = y) && y > 0)
			{
				trace_ligne(/*a, b*/xa, ya, x, y, ptr, TIP.col[0], 1);
/*				TEST2
					ft_putnbr(x - xa); NL
					ft_putnbr(sqrt(pow(y - ya, 2) + pow(x - xa, 2))); NL
					ft_putnbr(((y - ya > 0 ? -1 : 1) * 180 / M_PI)* acos((x - xa) / sqrt(pow(y - ya, 2) + pow(x - xa, 2)))); NL
				TEST4*/
			}
	}
	else if (*k == 3 && !ft_polygone(key, x, y, ptr))
		*k = -1;
}

void	ft_change_color(long *col, int i)
{
	int			tmp;
	static int	pui[2] = {1, 1};
	static int	neg[2] = {1, 1};

	if (*col % 0xffffff != 0)
	{
		if ((tmp = (*col / (int)pow(256, pui[i])) % 256) % 255 == 0)
			neg[i] = 1 - (2 * tmp / 255);
		*col += CHCOL * neg[i] * pow(256, pui[i]);
		if ((*col / (int)pow(256, pui[i])) % 255 == 0)
		{
			pui[i] += 1;
			if ((pui[i] + 1) % 4 == 0)
				pui[i] = (3 - pui[i]) / 2;
		}
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
}

int		pseudo_snake(int key, void *ptr)
{
	int				i;
	int				j;
	float			n;
	static int		k = 1;
	static int		col = 0xAAAAAA;
	static int		y = (HEIGHT / 2) + 1;
	static int		x = WIDTH / 2;
	t_test		*test;

	test = ptr;
//	ft_putnbr(key); NL
	n = 0.5;
	if (key == 6)
	{
		col = 0x000000;
		k = 1;
	}
	if (key == 12)
		k++;
	if (k % 2 == 0)
		ft_change_color(&TIP.col[0], 0);
	if (key == 124)
		x = (x < WIDTH ? x + PIX : PIX / 2 + 1);
	else if (key == 125)
		y = (y < HEIGHT ? y + PIX : PIX / 2 + 1);
	else if (key == 123)
		x = (x > 0 ? x - PIX : WIDTH - PIX / 2 - 1);
	else if (key == 126)
		y = (y > 0 ? y - PIX : HEIGHT - PIX / 2 - 1);
	else if (key == 49)
		n *= 3;
	j = -1;
	while (++j < 2 * PIX * n)
	{
		i = -1;
		while (++i < 2 * PIX * n)
			mlx_pixel_put(test->mlx_ptr, test->win_ptr, x + i - PIX * n,
					y + j - PIX * n, TIP.col[0]);
	}
	return (0);
}
