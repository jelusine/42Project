/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 03:18:18 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/03 09:24:34 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fractol.h"

int		ft_exit(int key, void *ptr)
{
	(void)key;
	(void)ptr;
	exit(0);
}

void	set_val(t_test *test, int s, int k)
{
	TFP[s].zoom = 200;
	TFP[s].ite_max = 51 * k + (1 - k) * TFP[s].ite_max;
	TFP[s].n = 2 * k + (1 - k) * TFP[s].n;
	TFP[s].limxy[1] = -1.25 - ((SAVE + 1) % 2) * SAVE * 0.325 * (1 - s);
	TFP[s].limxy[0] = 0.5 * s - 2.5 + ((SAVE + 1) % 2) * SAVE * 0.05 * (1 - s);
	if (s == 1 && k)
	{
		test->jc.r = 0.285;
		test->jc.i = 0.01;
	}
}

int		ft_initializer(t_test *test)
{
	int		s;

	test->win_ptr = mlx_new_window(test->mlx_ptr, WIDTH, HEIGHT, "Fractol");
	s = 2;
	while (--s >= 0)
	{
		set_val(test, s, 1);
		TFP[s].img_ptr = mlx_new_image(test->mlx_ptr, WIDTH, HEIGHT);
		TFP[s].data = mlx_get_data_addr(TFP[s].img_ptr, &TFP[s].bpp,
			&TFP[s].sl, &TFP[s].endian);
		fractest(test, -1, s);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_test	test;

	if ((ac != 2) || (ft_strcmp("Mandelbrot", av[1])
			&& ft_strcmp("Julia", av[1])
				&& ft_strcmp("Burning_Ship", av[1])
					&& ft_strcmp("Multibrot", av[1])))
		return (ft_errormsg(ERRMSG));
	test.mlx_ptr = mlx_init();
	test.s = (1 - (av[1][0] % 2)) * (10 - av[1][0] / 8);
	test.save = 1 * test.s;
	test.f = frac_mandeljul;
	if (av[1][0] == 'M' && av[1][1] == 'u')
		test.f = frac_multibrot;
	else if (test.s == 2)
		test.f = &frac_burning_ship;
	test.lock = -1 + ft_initializer(&test);
	test.s %= 2;
	fractest(&test, 0, test.s);
	mlx_key_hook(test.win_ptr, ft_key, &test);
	mlx_mouse_hook(test.win_ptr, ft_mouse, &test);
	mlx_hook(test.win_ptr, 6, 1L << 8, ft_tracking, &test);
	mlx_hook(test.win_ptr, 17, 0, ft_exit, &test);
	mlx_loop(test.mlx_ptr);
	return (0);
}
