/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 09:05:56 by jelusine          #+#    #+#             */
/*   Updated: 2018/08/14 13:27:49 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void		del_str(void *str, size_t len)
{
	(void)len;
	ft_strdel((char **)str);
}

void		ft_set_npoint(t_test *test, float z, float cst)
{
	int			y;
	int			x;
	int			ecart;
	float		ymin;
	float		ymax;
	float		tmp;
	const int	nwidth = WIDTH / (test->grid->lenx + test->grid->leny);
	float			nheight = HEIGHT / (test->grid->lenx + test->grid->leny);

	ft_putnbr(nheight * 100); TEST3
	test->grid->cstc += cst;
	test->grid->zc += z;
	tmp = (((TABP[test->grid->leny - 1][0].x) -
	(TABP[test->grid->leny - 1][0].y)) * (test->grid->cstc)) + nwidth;
	ymin = HEIGHT;
	ymax = 0;
	y = -1;
	ecart = (WIDTH % (test->grid->lenx + test->grid->leny)) / 2;
	ft_putnbr(ecart); TEST3
	if (nheight < 1)
	{
		TEST2
		nheight = 0.7;
		ecart = 0;
	}
//	ft_putnbr(HEIGHT); TEST3
//	ft_putnbr(test->grid->lenx + test->grid->leny); TEST3
	while (++y < test->grid->leny)
	{
		x = -1;
		while (++x < test->grid->lenx)
		{
			TABP[y][x].xa = (((TABP[y][x].x) - (TABP[y][x].y)) *
				(test->grid->cstc)) + ((x + test->grid->leny - y) * nwidth)
					- tmp/* + ecart*/ + 1;
			TABP[y][x].ya = (((TABP[y][x].x + TABP[y][x].y) *
				(test->grid->cstc / 2)) - (TABP[y][x].z * test->grid->zc))
				+ ((x + y) * nheight);
			ymax = (TABP[y][x].ya > ymax ? TABP[y][x].ya : ymax);
			ymin = (TABP[y][x].ya < ymin ? TABP[y][x].ya : ymin);
		}
	}
	TIP.width = TABP[0][test->grid->lenx - 1].xa -
		TABP[test->grid->leny - 1][0].xa + nwidth + 2 * ecart;
	ecart = HEIGHT % (test->grid->lenx + test->grid->leny) / 2;
	y = -1;
	while (++y < test->grid->leny)
	{
		x = -1;
		while (++x < test->grid->lenx)
			TABP[y][x].ya += nheight + ecart - ymin;
	}
	TIP.height = ymax - ymin + nheight + 2 * ecart;
}

void		ft_affiche_point(t_test test)
{
	int			y;
	int			x;

	trace_ligne(0, 0, TI.width, 0, &test, 0xffffff, 0);
	trace_ligne(0, 0, 0, TI.height, &test, 0xffffff, 0);
	trace_ligne(TI.width - 1, 0, TI.width - 1, TI.height - 1, &test, 0xffffff, 0);
	trace_ligne(0, TI.height - 1, TI.width, TI.height - 1, &test, 0xffffff, 0);
	y = -1;
	while (++y < test.grid->leny)
	{
		x = -1;
		while (++x < test.grid->lenx)
		{
			if (x > 0)
				trace_ligne(/*TAB[y][x - 1].pa, TAB[y][x].pa*/TAB[y][x - 1].xa,
						TAB[y][x - 1].ya,TAB[y][x].xa,TAB[y][x].ya, &test,
					(TAB[y][x].z || TAB[y][x - 1].z ? TI.col[0] : TI.col[1]), 0);
			if (y > 0)
				trace_ligne(/*TAB[y - 1][x].pa, TAB[y][x].pa*/TAB[y - 1][x].xa,
						TAB[y - 1][x].ya,TAB[y][x].xa, TAB[y][x].ya, &test,
					(TAB[y][x].z || TAB[y - 1][x].z ? TI.col[0] : TI.col[1]), 0);
		}
	}
}
