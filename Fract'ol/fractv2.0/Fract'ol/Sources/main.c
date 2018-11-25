/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 03:18:18 by jelusine          #+#    #+#             */
/*   Updated: 2018/11/25 08:24:48 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fractol.h"

int		ft_exit(int key, void *ptr)
{
	(void)key;
	(void)ptr;
	exit(0);
}

void	set_val(t_test *test)
{
	const t_point p = {(S % 2) + 1, (S + 1) % 3, (S + 1) % 2};

	test->zoom[S] = 200;
	test->ite_max[S] = 50;
	test->limxy[S][1] = -1.9 + (p.y / p.x) * 0.65;
	test->limxy[S][0] = -2 - (p.z * (((1 - p.y) * 0.4) + (p.y * 0.5)));
	if (S == 1)
	{
		test->jc.r = 0.285;
		test->jc.i = 0.01;
	}
}

int		ft_initializer(t_test *test)
{
	test->win_ptr = mlx_new_window(test->mlx_ptr, WIDTH, HEIGHT, "Fractol");
	test->s = 3;
	while (--test->s >= 0)
	{
		set_val(test);
		TIP[S].img_ptr = mlx_new_image(test->mlx_ptr, WIDTH, HEIGHT);
		TIP[S].data = mlx_get_data_addr(TIP[S].img_ptr, &TIP[S].bpp,
				&TIP[S].sl, &TIP[S].endian);
		fractest(test, -1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_test	test;

	if ((ac != 2) || (ft_strcmp("Mandelbrot", av[1])
						&& ft_strcmp("Julia", av[1])
						&& ft_strcmp("Burning_Ship", av[1])))
		return (ft_errormsg(ERRMSG));
	test.mlx_ptr = mlx_init();
	test.lock = -1 + ft_initializer(&test);
	test.s = (1 - (av[1][0] % 2)) * (10 - av[1][0] / 8);
	fractest(&test, 0);
	mlx_key_hook(test.win_ptr, ft_key, &test);
	mlx_mouse_hook(test.win_ptr, ft_mouse, &test);
	mlx_hook(test.win_ptr, 6, 1L << 8, ft_tracking, &test);
	mlx_hook(test.win_ptr, 17, 0, ft_exit, &test);
	mlx_loop(test.mlx_ptr);
	return (0);
}
