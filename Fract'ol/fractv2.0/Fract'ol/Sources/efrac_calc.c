/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efrac_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 05:20:28 by jelusine          #+#    #+#             */
/*   Updated: 2018/11/25 08:16:12 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fractol.h"

long	ft_calcol(t_test *test, int x, int y)
{
	const int	ij[2] = {(S + 1) % 2, 1 - ij[0]};
	t_nima		zc[2];
	double		tmp;
	int			ite;
	long		col;

	zc[ij[0]].r = x / test->zoom[S] + test->limxy[S][0];
	zc[ij[0]].i = y / test->zoom[S] + test->limxy[S][1];
	zc[ij[1]].r = 0 + ij[1] * test->jc.r;
	zc[ij[1]].i = 0 + ij[1] * test->jc.i;
	col = 0xffff00;
	ite = -1;
	while (++ite < test->ite_max[S]
			&& zc[0].r * zc[0].r + zc[0].i * zc[0].i < 4)
	{
		tmp = zc[0].r;
		zc[0].r = tmp * tmp - zc[0].i * zc[0].i + zc[1].r;
		zc[0].i = 2 * zc[0].i * tmp + zc[1].i;
		if (test->s + 1 == 3 && ((zc[0].r = fabs(zc[0].r)) || 1))
			zc[0].i = fabs(zc[0].i - zc[1].i) + zc[1].i;
		col -= 16 * 256 * 256;
	}
	if (test->ite_max[S] > ite)
		return (col);
	return (0);
}

int		fractest(void *data, int k)
{
	t_point			p;
	t_test			*test;
	long			col;
	unsigned char	rgb[3];

	test = data;
	p.y = -1;
	while (k && ++p.y < HEIGHT && ((p.x = -1) || 1))
	{
		while (++p.x < WIDTH)
		{
			col = ft_calcol(test, p.x, p.y);
			p.z = p.y * TIP[S].sl + (int)(p.x * TIP[S].bpp * 0.125);
			rgb[2] = ((col & 0xFF000000) >> 24);
			rgb[1] = ((col & 0xFF0000) >> 16);
			rgb[0] = ((col & 0xFF00) >> 8);
			TIP[S].data[p.z] = rgb[0];
			TIP[S].data[p.z + 1] = rgb[1];
			TIP[S].data[p.z + 2] = rgb[2];
		}
	}
	if (k >= 0)
		mlx_put_image_to_window(test->mlx_ptr, test->win_ptr,
				TIP[S].img_ptr, 0, 0);
	return (0);
}

int		ft_tracking(int x, int y, void *ptr)
{
	t_test	*test;

	test = ptr;
	if (test->lock > 0 && S == 1)
	{
		test->jc.r = x / test->zoom[S] + test->limxy[S][0];
		test->jc.i = y / test->zoom[S] + test->limxy[S][1];
		fractest(test, 1);
	}
	return (0);
}

int		ft_key(int key, void *ptr)
{
	t_test	*test;
	int		i;

	test = ptr;
	if (key == 53)
		exit(1);
	if ((i = 1) && ((key == 123 && test->ite_max[S] > 1)
			|| (key == 124 && test->ite_max[S] < 1000)))
	{
		if (key == 123)
			test->ite_max[S] -= (test->ite_max[S] > 10 ? 10 : 1);
		else
			test->ite_max[S] += (test->ite_max[S] >= 10 ? 10 : 1);
	}
	else if (key == 0 || key == 2 || key == 13 || key == 1)
		test->limxy[S][key % 2] += (40 / test->zoom[S])
			* ((key - 1) * (1 - key % 2) + (key % 2) * (7 - key) / 6);
	else if (key == 36 && (test->lock = -1))
		set_val(test);
	else if (key == 49)
		test->lock *= -1 + --i;
	else if ((key == 125 || key == 126) && (test->lock = --i - 1))
		if (((test->s += 2 * key - 251) + 1) % 4 == 0)
			test->s = (3 - test->s) * 0.5;
	return (fractest(test, i));
}

int		ft_mouse(int key, int x, int y, void *ptr)
{
	t_test *test;

	test = ptr;
	if (key == 4 || key == 5)
	{
		test->zoom[S] *= (1.25 * (1 - key % 2)) + (0.8 * (key % 2));
		test->limxy[S][0] += (x - (WIDTH * 0.5)) / test->zoom[S];
		test->limxy[S][1] += (y - (HEIGHT * 0.5)) / test->zoom[S];
		return (fractest(test, 1));
	}
	return (0);
}
