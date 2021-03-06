/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 09:05:56 by jelusine          #+#    #+#             */
/*   Updated: 2018/11/16 23:50:24 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

int		ft_set_map(void *ptr, char *path)
{
	t_test *test;

	test = ptr;
	TIP.pos[1] = 0;
	TIP.ref.x = ++test->lock;
	if (!(test->grid = ft_parser(path, test)))
		return (ft_errormsg("Error map\n"));
	ft_set_npoint(test, 0, 0);
	TIP.pos[0] = (WIDTH - TABP[0][test->grid->lenx - 1].a[0]) / 2;
	TIP.img_ptr = mlx_new_image(test->mlx_ptr, TIP.wihei[0], TIP.wihei[1]);
	TIP.data = mlx_get_data_addr(TIP.img_ptr, &TIP.bpp, &TIP.sl, &TIP.endian);
	ft_affiche_point(*test);
	return (1);
}

/*
** Pseudo fdf:
**
** 1) Gestion Couleur
** 2) Gestion Zoom
** 3) Gestion Hauteur
** 4) Ground Zero
*/

int		pseudo_fdf(int key, void *ptr)
{
	int			tmp;
	t_test		*test;

	test = ptr;
	if (key == 16 || key == 17)
		ft_change_color(&TIP.col[key - 16], key - 16);
	else if ((key == 91 && TGP->cstc < 5)
			|| (key == 84 && TGP->cstc > 0.01))
		ft_set_npoint(test, 0, 1.25 * (key % 2) + (0.8 * (1 - key % 2)));
	else if ((key == 69 || key == 78)
			&& ((tmp = floor(TABP[(int)TIP.ref.y][(int)TIP.ref.x].a[1])) || 1)
			&& !ft_set_npoint(test, -0.1 * pow(-1, key % 2), 1))
		TIP.pos[1] -= floor(TABP[(int)TIP.ref.y][(int)TIP.ref.x].a[1]) - tmp;
	else if (key == 36 && (test->lock = -1)
			&& !(TIP.pos[1] = 0) && !ft_set_npoint(test, -TGP->zc, 0))
		TIP.pos[0] = (WIDTH - TABP[0][TGP->lenx - 1].a[0]) / 2;
	else
		return (0);
	mlx_destroy_image(test->mlx_ptr, TIP.img_ptr);
	TIP.img_ptr = mlx_new_image(test->mlx_ptr, TIP.wihei[0], TIP.wihei[1]);
	TIP.data = mlx_get_data_addr(TIP.img_ptr, &TIP.bpp, &TIP.sl, &TIP.endian);
	return (ft_affiche_point(*test));
}

float	ft_calc_point(t_test *test, int ecart, const float wh[2], float *ymin)
{
	float		ymax;
	int			tmp;
	int			y;
	int			x;

	*ymin = HEIGHT;
	ymax = 0;
	tmp = (1 - test->grid->leny) * CST2 + wh[0];
	y = -1;
	while (++y < test->grid->leny && (x = -1))
	{
		while (++x < test->grid->lenx)
		{
			TABP[y][x].a[0] = ((x - y) * CST2)
				+ ((x + TGP->leny - y) * wh[0]) - tmp + ecart + 1;
			TABP[y][x].a[1] = (x + y) * ((CST2 / 2) + wh[1])
				- (TABP[y][x].z * TGP->zc);
			ymax = (TABP[y][x].a[1] > ymax ? TABP[y][x].a[1] : ymax);
			*ymin = (TABP[y][x].a[1] < *ymin ? TABP[y][x].a[1] : *ymin);
		}
	}
	if ((TIP.wihei[0] = TABP[0][TGP->lenx - 1].a[0]
		- TABP[TGP->leny - 1][0].a[0] + wh[0] + 2 * ecart) > 16000)
		return (-1);
	return (ymax);
}

int		ft_set_npoint(t_test *test, float z, float cst)
{
	t_pointa	p;
	int			ecart;
	float		yia[2];
	float		wh[2];

	if ((TGP->cstc *= cst) <= 0)
		TGP->cstc = 1;
	TGP->zc += z;
	p.z = 1;
	while ((TGP->lenx + TGP->leny) > WIDTH * p.z
			|| (TGP->lenx + TGP->leny) > HEIGHT * p.z)
		p.z++;
	ecart = (p.z * WIDTH % (test->grid->lenx + test->grid->leny)) / 2;
	wh[0] = TGP->cstc * (p.z * WIDTH / (TGP->lenx + TGP->leny));
	wh[1] = TGP->cstc * (p.z * HEIGHT / (TGP->lenx + TGP->leny));
	if ((yia[1] = ft_calc_point(test, ecart, wh, &yia[0])) < 0)
		return (ft_set_npoint(test, 0, 0));
	ecart = p.z * HEIGHT % (TGP->lenx + TGP->leny) / 2;
	p.y = -1;
	while (++p.y < TGP->leny && (p.x = -1))
		while (++p.x < TGP->lenx)
			TABP[p.y][p.x].a[1] += wh[1] + ecart - yia[0];
	if ((TIP.wihei[1] = yia[1] - yia[0] + wh[1] + 2 * ecart) > 16382)
		ft_set_npoint(test, -TGP->zc, 1);
	return (0);
}

int		ft_affiche_point(t_test test)
{
	int			y;
	int			x;

	y = -1;
	while (++y < test.grid->leny && (x = -1))
	{
		while (++x < test.grid->lenx)
		{
			if (x > 0)
				trace_ligne(TAB[y][x - 1].a, TAB[y][x].a, &test,
					(TAB[y][x].z || TAB[y][x - 1].z ? 0 : 1));
			if (y > 0)
				trace_ligne(TAB[y - 1][x].a, TAB[y][x].a, &test,
					(TAB[y][x].z || TAB[y - 1][x].z ? 0 : 1));
		}
	}
	return (0);
}
