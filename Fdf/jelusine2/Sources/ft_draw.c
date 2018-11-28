/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 03:04:43 by jelusine          #+#    #+#             */
/*   Updated: 2018/11/16 23:49:41 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

void	del(void *content, size_t size)
{
	(void)size;
	ft_strdel((char**)&content);
}

void	pix_img(t_test *test, int y, int x, unsigned int col)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	b = ((col & 0xFF000000) >> 24);
	g = ((col & 0xFF0000) >> 16);
	r = ((col & 0xFF00) >> 8);
	if (x < TIP.wihei[0] && y < TIP.wihei[1])
	{
		test->img.data[y * test->img.sl + x * test->img.bpp / 8] = r;
		test->img.data[y * test->img.sl + x * test->img.bpp / 8 + 1] = g;
		test->img.data[y * test->img.sl + x * test->img.bpp / 8 + 2] = b;
	}
}

void	put_point(int tval[7][2], int i, t_test *test)
{
	while (tval[5][0] <= tval[6][0] || tval[5][1] != tval[6][1])
	{
		if (tval[2][0] > 0 || (tval[2][0] <= 0 && tval[0][0] >= tval[1][0]))
			tval[5][0]++;
		if (tval[2][0] > 0 || (tval[2][0] <= 0 && tval[0][0] < tval[1][0]))
			tval[5][1] += (tval[6][1] - tval[5][1] > 0 ? 1 : -1);
		tval[2][0] += (tval[2][0] <= 0 ? tval[3][0] : tval[4][0]);
		if (i == -1)
			ft_tracecrox(tval[5], test, TIP.col[0], (test->bold * 2) + 1);
		else
			pix_img(test, tval[5][1], tval[5][0], TIP.col[i] * 256);
		if (tval[5][0] == tval[6][0] && tval[5][1] == tval[6][1])
			break ;
	}
}

void	trace_ligne(int a[2], const int b[2], void *ptr, int i)
{
	int		tval[7][2];
	t_test	*test;

	test = ptr;
	tval[5][0] = a[0];
	tval[5][1] = a[1];
	tval[6][0] = b[0];
	tval[6][1] = b[1];
	if (tval[5][0] > tval[6][0] && ft_swap(&tval[5][0], &tval[6][0]))
		ft_swap(&tval[5][1], &tval[6][1]);
	tval[0][0] = tval[6][0] - tval[5][0];
	tval[1][0] = ft_abs(tval[6][1] - tval[5][1]);
	tval[3][0] = 2 * ft_min(tval[0][0], tval[1][0]);
	tval[2][0] = tval[3][0] - ft_max(tval[0][0], tval[1][0]);
	tval[4][0] = -2 * ft_abs(tval[1][0] - tval[0][0]);
	put_point(tval, i, test);
}

void	ft_sample(const t_test *test)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 10 + test->bold * 2 && (x = -1))
	{
		while (++x < 110 + test->bold * 2)
			mlx_pixel_put(test->mlx_ptr, test->win_ptr,
					1595 - test->bold + x, 95 + y - test->bold, 0x000000);
	}
}
