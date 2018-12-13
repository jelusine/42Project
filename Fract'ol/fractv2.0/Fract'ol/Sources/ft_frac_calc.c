/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frac_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 05:20:28 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/03 08:30:59 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fractol.h"

void	frac_mandeljul(double *r, double *i, t_nima cst, int n)
{
	const double tmp = *r;

	(void)n;
	*r = tmp * tmp - *i * *i + cst.r;
	*i = 2 * *i * tmp + cst.i;
}

void	frac_multibrot(double *r, double *i, t_nima cst, int n)
{
	const double	tmp = *r;
	double			j;
	double			k;

	j = pow((tmp * tmp) + (*i * *i), n / 2);
	k = n * atan2(*i, tmp);
	*r = j * cos(k) + cst.r;
	*i = j * sin(k) + cst.i;
}

void	frac_burning_ship(double *r, double *i, t_nima cst, int n)
{
	const double tmp = *r;

	(void)n;
	*r = fabs(tmp * tmp - *i * *i + cst.r);
	*i = fabs(2 * *i * tmp) + cst.i;
}

long	ft_calcol(t_test *test, int x, int y, const int ijs[3])
{
	t_nima		zc[2];
	int			ite;
	long		col;

	zc[ijs[0]].r = x / TFP[ijs[2]].zoom + TFP[ijs[2]].limxy[0];
	zc[ijs[0]].i = y / TFP[ijs[2]].zoom + TFP[ijs[2]].limxy[1];
	zc[ijs[1]].r = 0 + ijs[1] * test->jc.r;
	zc[ijs[1]].i = 0 + ijs[1] * test->jc.i;
	col = 0xffff00;
	ite = -1;
	while (++ite < TFP[ijs[2]].ite_max
			&& zc[0].r * zc[0].r + zc[0].i * zc[0].i < 4)
	{
		test->f(&zc[0].r, &zc[0].i, zc[1], TFP[ijs[2]].n);
		col -= 16 * 256 * 256;
	}
	if (TFP[ijs[2]].ite_max > ite)
		return (col);
	return (0);
}

int		fractest(t_test *test, int k, int s)
{
	const int		ijs[3] = {(s + 1) % 2, 1 - ijs[0], s};
	t_point			p;
	long			col;
	unsigned char	rgb[3];

	p.y = -1;
	while (k && ++p.y < HEIGHT && ((p.x = -1) || 1))
	{
		while (++p.x < WIDTH)
		{
			col = ft_calcol(test, p.x, p.y, ijs);
			p.z = p.y * TFP[s].sl + (int)(p.x * TFP[s].bpp * 0.125);
			rgb[2] = ((col & 0xFF000000) >> 24);
			rgb[1] = ((col & 0xFF0000) >> 16);
			rgb[0] = ((col & 0xFF00) >> 8);
			TFP[s].data[p.z] = rgb[0];
			TFP[s].data[p.z + 1] = rgb[1];
			TFP[s].data[p.z + 2] = rgb[2];
		}
	}
	if (k >= 0)
		mlx_put_image_to_window(test->mlx_ptr, test->win_ptr,
				TFP[s].img_ptr, 0, 0);
	return (0);
}
