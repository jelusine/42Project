/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:52:49 by jelusine          #+#    #+#             */
/*   Updated: 2018/07/08 14:34:09 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./fdf.h"

void	ft_tracecrox(int x, int y, void *ptr, int color)
{
	int i;
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
//	static t_pointa	a = {-1, -1, -1};
	static int	xa = -1;
	static int	ya = -1;

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
					&& (b.y = y))
				trace_ligne(/*a, b*/xa, ya, x, y, ptr, 0x00ff00, 1);
	}
	else if (*k == 3 && !ft_polygone(key, x, y, ptr))
		*k = -1;
}

int		pseudo_snake(int key, void *ptr)
{
	int				i;
	int				j;
	float			n;
	static int		k = 1;
	static int		col = 0xAAAAAA;
	static int		y = HEIGHT / 2;
	static int		x = WIDTH / 2;
	const t_test	*test = ptr;

	n = 0.5;
	if (key == 6)
	{
		col = 0x000000;
		k = 1;
	}
	if (key == 12)
		k++;
	if (k % 2 == 0)
		col += random();
	if (key == 124)
		x = (x < WIDTH ? x + PIX: PIX / 2 + 1);
	if (key == 125)
		y = (y < HEIGHT ? y + PIX: PIX / 2 + 1);
	if (key == 123)
		x = (x > 0 ? x - PIX: WIDTH - PIX / 2 - 1);
	if (key == 126)
		y = (y > 0 ? y - PIX: HEIGHT - PIX / 2 - 1);
	if (key == 49)
		n *= 3;
	j = -1;
	while (++j < 2 * PIX * n)
	{
		i = -1;
		while (++i < 2 * PIX * n)
			mlx_pixel_put(test->mlx_ptr, test->win_ptr, x + i - PIX * n,
					y + j - PIX * n, col);
	}
	return (0);
}
