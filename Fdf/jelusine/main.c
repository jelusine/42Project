/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:11:50 by jelusine          #+#    #+#             */
/*   Updated: 2018/09/11 03:03:51 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int		ft_mouse(int key, int x, int y, void *ptr)
{
	t_test		*test;
	t_pointa	told[2];
	const int	coor[2] = {x, y};
	static int	nk[2] = {0, -1};

	test = ptr;
	if (key == 1 && nk[1] == -1 && y >= 0 && (test->lock *= -1)
			&& (test->lockx = x - TIP.pos[0]) + 1)
		test->locky = y - TIP.pos[1];
	else if (test->lock % 2 == 0 && (test->lock = -ft_abs(test->lock)))
		ft_paintashier(key, coor, ptr, &nk[1]);
	else if ((key == 4 && test->grid->cstc < test->lim)
			|| (key == 5 && test->grid->cstc > test->limmin))
	{
		told[1].x = TIP.wihei[0];
		told[0].x = x - TIP.pos[0];
		told[1].y = TIP.wihei[1];
		told[0].y = y - TIP.pos[1];
		pseudo_fdf(119 - 7 * key, ptr);
		test->lockx = told[0].x * TIP.wihei[0] / told[1].x + (nk[0] % 2);
		test->locky = told[0].y * TIP.wihei[1] / told[1].y + (nk[0]++ % 2);
		TIP.pos[0] = x - test->lockx;
		TIP.pos[1] = y - test->locky;
	}
	return (0);
}

int		ft_keyboard(int key, void *ptr)
{
	int				i;
	t_test			*test;
	const int		m = key % 2;
	const int		keyset[18] = {123, 124, 125, 126, 6, 49, 12,
								0, 1, 2, 13, 91, 84, 69, 78, 36, 16, 17};

	test = ptr;
	if (key == 53)
		exit(1);
	if (key == 117)
		return (mlx_clear_window(test->mlx_ptr, test->win_ptr));
	i = 0;
	while (i < 18 && keyset[i] != key)
		i++;
	if (i < 18)
	{
		if (test->lock % 2 == 0 && i < 7)
			return (pseudo_snake(key, ptr));
		else if (i >= 11 && test->grid)
			return (pseudo_fdf(key, ptr));
		else if (((key == 13 || key == 0) && TIP.pos[m] + TIP.wihei[m] > 100)
				|| ((key == 1 || key == 2) && TIP.pos[m] < test->lola[m] - 100))
			TIP.pos[m] += 10 * pow(-1, m == 0 ? (key + 1) % 3 : (key - 1) / 12);
	}
	return (0);
}

/*
** pnta[2] dans ptit_test:
** Impossible de le mettre en "const int" car
** la fonction trace_ligne prend un "int" en premier parametre.
*/

int		ptit_test(void *ptr)
{
	int				pnta[2];
	const int		pntb[2] = {1700, 100};
	const t_test	*test = ptr;

	pnta[0] = 1600;
	pnta[1] = 100;
	if (test->lock % 2 == 0)
	{
		ft_sample(test);
		trace_ligne(pnta, pntb, ptr, -1);
	}
	else
	{
		mlx_clear_window(test->mlx_ptr, test->win_ptr);
		mlx_put_image_to_window(test->mlx_ptr, test->win_ptr, TIP.img_ptr,
			TIP.pos[0], TIP.pos[1]);
	}
	return (1);
}

int		ft_tracking(int x, int y, void *ptr)
{
	t_test		*test;
	const int	ttt[2] = {x, y};
	static int	tt[2] = {-1, -1};

	test = ptr;
	if (test->lock > 0)
	{
		if (test->lock == 2 && tt[0] >= 0)
			if (tt[0] >= 0)
				trace_ligne(tt, ttt, test, -1);
		tt[0] = x - (test->lockx * (test->lock % 2));
		tt[1] = y - (test->locky * (test->lock % 2));
		if (test->lock == 1)
		{
			if (100 < tt[0] + TIP.wihei[0] && tt[0] < WIDTH - 100)
				TIP.pos[0] = x - test->lockx;
			if (100 < tt[1] + TIP.wihei[1] && tt[1] < HEIGHT - 100)
				TIP.pos[1] = y - test->locky;
		}
	}
	else if ((tt[0] = -1))
		tt[1] = -1;
	return (0);
}

int		main(int ac, char **av)
{
	t_test	test;

	test.mlx_ptr = mlx_init();
	test.win_ptr = mlx_new_window(test.mlx_ptr, WIDTH, HEIGHT,
			(ac == 2 ? av[1] : "Test"));
	test.bold = 0;
	test.grid = NULL;
	test.lock = -2;
	test.img.col[0] = 0xff0000;
	test.img.col[1] = 0x00ffff;
	if (ac == 2 && !ft_set_map(&test, av[1]))
		return (0);
	mlx_hook(test.win_ptr, 2, 1, ft_keyboard, &test);
	mlx_mouse_hook(test.win_ptr, ft_mouse, &test);
	mlx_hook(test.win_ptr, 6, 1L << 8, ft_tracking, &test);
	mlx_hook(test.win_ptr, 17, 0, ft_exit, 0);
	mlx_loop_hook(test.mlx_ptr, ptit_test, &test);
	mlx_loop(test.mlx_ptr);
	return (0);
}
