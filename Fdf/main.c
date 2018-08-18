/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:11:50 by jelusine          #+#    #+#             */
/*   Updated: 2018/08/14 14:58:29 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int		ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return (1);
}

void	pix_img(void *ptr, int y, int x, unsigned int col)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	t_test	*test = ptr;

	b = ((col & 0xFF000000) >> 24);
	g = ((col & 0xFF0000) >> 16);
	r = ((col & 0xFF00) >> 8);
	test->img.data[y * test->img.sl + x * test->img.bpp / 8] = r;
	test->img.data[y * test->img.sl + x * test->img.bpp / 8 + 1] = g;
	test->img.data[y * test->img.sl + x * test->img.bpp / 8 + 2] = b;
}


void	trace_ligne(/*t_pointa a, t_pointa b*/int xa, int ya, int xb, int yb, void *ptr, long col, int i)
{
	int				tval[5];
	const t_test	*test = ptr;

	if (xa > xb && ft_swap(&xa, &xb))
		ft_swap(&ya, &yb);
	tval[0] = xb - xa;
	tval[1] = ft_abs(yb - ya);
	tval[2] = 2 * ft_min(tval[0], tval[1]) - ft_max(tval[0], tval[1]);
	tval[3] = 2 * ft_min(tval[0], tval[1]);
	tval[4] = -2 * ft_abs(tval[1] - tval[0]);
	while (xa <= xb || ya != yb)
	{
		if (tval[2] > 0 || (tval[2] <= 0 && tval[0] >= tval[1]))
			xa++;
		if (tval[2] > 0 || (tval[2] <= 0 && tval[0] < tval[1]))
			ya += (yb - ya > 0 ? 1 : -1);
		tval[2] += (tval[2] <= 0 ? tval[3] : tval[4]);
		if (i == 1)
			mlx_pixel_put(test->mlx_ptr, test->win_ptr, xa, ya, col);
		else
			pix_img(ptr, ya, xa, col * 256);
		if (xa == xb && ya == yb)
			break ;
	}
}

int		ft_test_mouse(int key, int x, int y, void *ptr)
{
	t_pointa	tmp;
	t_pointa	old;
	t_test		*test = ptr;
	static int	n = 0;
	static int	k = -1;

	if (key == 1 && k == -1 && y >= 0 && (test->lock *= -1) &&
			(test->lockx = x - TIP.pos[0]) + 1)
		test->locky = y - TIP.pos[1];
	else if(test->lock % 2 == 0 && (test->lock = -ft_abs(test->lock)))
		ft_paintashier(key, x, y, ptr, &k);
	else if ((key == 4 && test->grid->cstc < test->lim) ||
			(key == 5 && test->grid->cstc > test->limmin))
	{
		old.x = TIP.width;
		tmp.x = x - TIP.pos[0];
		old.y = TIP.height;
		tmp.y = y - TIP.pos[1];
		pseudo_fdf((key == 4 ? 91 : 84), ptr);
		test->lockx = tmp.x * TIP.width / old.x + (n % 2);
		test->locky = tmp.y * TIP.height / old.y + (n++ % 2);
		TIP.pos[0] = x - test->lockx;
		TIP.pos[1] = y - test->locky;
	}
	return (0);
}

int		pseudo_fdf(int key, void *ptr)
{
	int			tmp;
	t_test		*test = ptr;

	if (key == 16 || key == 17)
		ft_change_color(&TIP.col[key - 16], key - 16);
	else if ((key == 91 && TGP->cstc < test->lim) ||
			(key == 84 && TGP->cstc > test->limmin))
		ft_set_npoint(test, 0, -1 * pow(-1, key % 2) / pow(10, test->pzoom));
	else if (key == 69 || key == 78)
	{
		tmp = floor(TABP[(int)TIP.ref.y][(int)TIP.ref.x].ya);
		ft_set_npoint(test, -0.1 * pow(-1, key % 2), 0);
		TIP.pos[1] -= floor(TABP[(int)TIP.ref.y][(int)TIP.ref.x].ya) - tmp;
	}
	else if (key == 36)
	{
		test->lock = -1;
		test->img.pos[1] = 0;
		ft_set_npoint(test, -test->grid->zc, -test->grid->cstc + CST2);
		TIP.pos[0] = (WIDTH - TABP[0][test->grid->lenx - 1].xa) / 2;
	}
	mlx_destroy_image(test->mlx_ptr, TIP.img_ptr);
	TIP.img_ptr = mlx_new_image(test->mlx_ptr, TIP.width, TIP.height);
	TIP.data = mlx_get_data_addr(TIP.img_ptr, &TIP.bpp, &TIP.sl, &TIP.endian);
	ft_affiche_point(*test);
	return (0);
}

int		ft_test(int key, void *ptr)
{
	int				i;
	t_test			*test;
	const int		keyset[] = {123, 124, 125, 126, 6, 49, 12,
								0, 1, 2, 13, 91, 84, 69, 78, 36, 16, 17};

	test = ptr;
	if (key == 53)
		exit(1);
	if (key == 117)
		return (mlx_clear_window(test->mlx_ptr, test->win_ptr));
//	if (test->lock % 2 == 0)
//		return (pseudo_snake(key, ptr));
	i = 0;
	while (i < 18 && keyset[i] != key)
		i++;
	if (i < 18)
	{
		if (i >= 11 && test->grid)
			return (pseudo_fdf(key, ptr));
		else if (i >= 7 && test->grid)
			TIP.pos[key % 2] += 10 * pow(-1, key % 2 == 0
				? (key + 1) % 3 : -((key % 13) - 1));
		else if (test->lock % 2 == 0)
			return (pseudo_snake(key, ptr));
	}
	return (0);
}

int		ptit_test(void *ptr)
{
	const t_test	*test = ptr;

	mlx_clear_window(test->mlx_ptr,test->win_ptr);
	mlx_put_image_to_window(test->mlx_ptr, test->win_ptr, TIP.img_ptr,
			TIP.pos[0], TIP.pos[1]);
	return (1);
}

int		test_mabit(int x, int y, void *ptr)
{
	static int	tt = -1;
	static int	ttt = -1;
	t_test	*test = ptr;

	if (test->lock > 0)
	{
		if (test->lock % 2 == 0)
		{
			if (tt >= 0)
				trace_ligne(tt, ttt, x, y , test, TIP.col[0], 1);
			tt = x;
			ttt = y;
		}
		else
		{
			TIP.pos[0] = x - test->lockx;
			TIP.pos[1] = y - test->locky;
		}
	}
	else
	{
		tt = -1;
		ttt = -1;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_test  test;

	test.mlx_ptr = mlx_init();
	test.win_ptr = mlx_new_window(test.mlx_ptr, WIDTH, HEIGHT, "Test");
	test.grid = NULL;
	test.lock = -2;
	test.img.col[0] = 0xff0000;
	test.img.col[1] = 0x00ffff;
/*	if ((ac == 4 || ac == 3) && (av[2][0] == 'G' || av[2][0] == 'F'))
	{
		test.img.col[av[2][0] - 70] = ft_atoi_base(&av[2][1], HEXAB);
		if (ac == 4 && (av[3][0] == 'G' || av[3][0] == 'F'))
			test.img.col[av[3][0] - 70] = ft_atoi_base(&av[3][1], HEXAB);
		ac = 2;
	}*/
	if (ac == 2)
	{
		TI.pos[1] = 0;
		TI.ref.x = ++test.lock;
		if (!(test.grid = ft_parser(av[1], &test)))
		{
			ft_putendl("Error map !");
			return (0);
		}
		ft_set_npoint(&test, 0, 0);
		TI.pos[0] = (WIDTH - TAB[0][test.grid->lenx - 1].xa) / 2;
		TI.img_ptr = mlx_new_image(test.mlx_ptr, TI.width, TI.height);
		TI.data = mlx_get_data_addr(TI.img_ptr, &TI.bpp, &TI.sl, &TI.endian);
		ft_affiche_point(test);
	}
	mlx_hook(test.win_ptr, 2, 1, ft_test, &test);
	mlx_mouse_hook(test.win_ptr, ft_test_mouse, &test);
	mlx_hook(test.win_ptr, 6, 1L<<8, test_mabit, &test);
	if (ac == 2)
		mlx_loop_hook(test.mlx_ptr, ptit_test, &test);
	mlx_loop(test.mlx_ptr);
	return (0);
}
