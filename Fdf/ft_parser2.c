/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 09:05:56 by jelusine          #+#    #+#             */
/*   Updated: 2018/07/15 21:06:29 by jelusine         ###   ########.fr       */
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
	const int	nheight = HEIGHT / (test->grid->lenx + test->grid->leny);

	test->grid->cstc += cst;
	test->grid->zc += z;
	tmp = (((TABP[test->grid->leny - 1][0].x) -
	(TABP[test->grid->leny - 1][0].y)) * (test->grid->cstc)) + nwidth;
	ymin = HEIGHT;
	ymax = 0;
	y = -1;
	ecart = (WIDTH % (test->grid->lenx + test->grid->leny)) / 2;
	TEST2
	ft_putstr("long larg: ");
	ft_putnbr(test->grid->lenx + test->grid->leny); NL
	ft_putstr("ecart prop: ");
	ft_putnbr(nwidth); NL
	ft_putstr("reste: ");
	ft_putnbr(ecart); NL
	while (++y < test->grid->leny)
	{
		x = -1;
		while (++x < test->grid->lenx)
		{
			TABP[y][x].xa = (((TABP[y][x].x) - (TABP[y][x].y)) *
					(test->grid->cstc)) + ((x + test->grid->leny - y + 1) * nwidth)
					- tmp + ecart;
//			ft_putnbr(TABP[y][x].xa);
//			ft_putchar(' ');
//			ft_putnbr(((int)(TABP[y][x].xa * 1000)) % 1000); NL
			TABP[y][x].ya = (((TABP[y][x].x + TABP[y][x].y) *
				(test->grid->cstc / 2)) - (TABP[y][x].z * test->grid->zc))
				+ ((x + y + 1) * nheight);
			ymax = (TABP[y][x].ya > ymax ? TABP[y][x].ya : ymax);
			ymin = (TABP[y][x].ya < ymin ? TABP[y][x].ya : ymin);
		}
	}
	ft_putnbr(WIDTH - TABP[0][test->grid->lenx - 1].xa); NL
	TIP.width = TABP[0][test->grid->lenx - 1].xa -
		TABP[test->grid->leny - 1][0].xa + nwidth + 2 * ecart;
	ft_putstr("taille img: ");
	ft_putnbr(TIP.width); NL
	TEST4
	ecart = HEIGHT % (test->grid->lenx + test->grid->leny) / 2;
	y = -1;
	while (++y < test->grid->leny)
	{
		x = -1;
		while (++x < test->grid->lenx)
		{
			TABP[y][x].ya += nheight + ecart - ymin;
			if (TABP[y][x].z == 0 && TIP.ref.x < 0)
			{
				TIP.ref.y = y;
				TIP.ref.x = x;
			}
		}
	}
	if (TIP.ref.x < 0)
		TIP.ref.y = 0 + ++TIP.ref.x;
	TIP.height = ymax - ymin + nheight + 2 * ecart;
}

void		ft_affiche_point(t_test test)
{
	int			y;
	int			x;
//	const int	ecart = (WIDTH % (test.grid->lenx + test.grid->leny)) / 2;
//	const int	nwidth = WIDTH / (test.grid->lenx + test.grid->leny);

	y = -1;
	while (++y < test.grid->leny)
	{
		x = -1;
		while (++x < test.grid->lenx)
		{
			if (x > 0)
				trace_ligne(/*TAB[y][x - 1].pa, TAB[y][x].pa*/TAB[y][x - 1].xa, TAB[y][x - 1].ya,TAB[y][x].xa,TAB[y][x].ya, &test,
					(TAB[y][x].z || TAB[y][x - 1].z ? 0xff00ff : 0xff8c00), 0);
			if (y > 0)
				trace_ligne(/*TAB[y - 1][x].pa, TAB[y][x].pa*/TAB[y - 1][x].xa,TAB[y - 1][x].ya,TAB[y][x].xa, TAB[y][x].ya, &test,
					(TAB[y][x].z || TAB[y - 1][x].z ? 0xff00ff : 0xff8c00), 0);
		}
	}
/*	y = 0;
	x = test.grid->lenx + test.grid->leny;
	while (++y < x)
	{
		trace_ligne((y + 0) * nwidth + ecart, 0, (y + 0) * nwidth + ecart, TI.height - 5,&test, 0xff8c22, 0);
		TEST5
		ft_putnbr(y * nwidth + ecart); NL
	}*/
}
