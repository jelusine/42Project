/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 03:18:18 by jelusine          #+#    #+#             */
/*   Updated: 2018/10/10 17:42:39 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Fract'ol.h"

int		ft_sign(double x)
{
	if (x < 0)
		return (-1);
	return (1);
}

void	pix_img(t_test *test, int y, int x, unsigned int col)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	b = ((col & 0xFF000000) >> 24);
	g = ((col & 0xFF0000) >> 16);
	r = ((col & 0xFF00) >> 8);
	test->img.data[y * test->img.sl + (int)(x * test->img.bpp * 0.125)] = r;
	test->img.data[y * test->img.sl + (int)(x * test->img.bpp * 0.125) + 1] = g;
	test->img.data[y * test->img.sl + (int)(x * test->img.bpp * 0.125) + 2] = b;
}

void	*fractest(void *data)
{
	int				y;
	int				x;
	int				ite;
	long			col;
	t_test			*test = data;
	int				dd_max;
	const int		s = test->sel_fra - 1;
	const int		i = test->sel_fra % 2;
	const int		j = 1 - i;
	t_nima			zc[2];
	double			tmp;

	pthread_mutex_lock(&test->thread.d_max);
	ft_putnbr(test->keyt); TEST3
	dd_max = WID_DIV * test->keyt--;
	if (test->keyt < 1)
	{
		pthread_cond_signal(&test->thread.s_cond);
		pthread_cond_wait(&test->thread.v_cond, &test->thread.d_max);
	}
	pthread_mutex_unlock(&test->thread.d_max);

	y = -1;
	while (++y < HEIGHT && ((x = dd_max - WID_DIV - 1) || 1))
	{
		while (++x < dd_max)
		{
			zc[i].r = x / test->zoom + test->limx[s][0];
			zc[i].i = y / test->zoom + test->limy[s][0];
			zc[j].r = 0 + j * test->jc.r;
			zc[j].i = 0 + j * test->jc.i;
			ite = -1;
			col = 0xffff00;
			while (pow(zc[0].r, 2) + pow(zc[0].i, 2) < 4 && ++ite < test->ite_max)
			{
				tmp = zc[0].r;
				zc[0].r = zc[0].r * zc[0].r - zc[0].i * zc[0].i + zc[1].r;
				zc[0].i = 2 * zc[0].i * tmp + zc[1].i;
				if (test->sel_fra == 3 && ((zc[0].r = fabs(zc[0].r)) || 1))
					zc[0].i = fabs(zc[0].i - zc[1].i) + zc[1].i;
				col -= 16 * 256 * 256;
			}
			pix_img(test, y, x, (ite != test->ite_max ? col : 0x000000));
		}
	}
	return (NULL);
}

void	test_th(t_test *test)
{
	int i;
	int ret;

	i = -1;
	while (++i < NB_TH)
	{
		ret = pthread_create(&test->thread.part[i], NULL, &fractest, test);
//		pthread_join(test->thread.part[i], NULL);
	}
/*	i = -1;
	while (++i < NB_TH)
	{
		pthread_join(test->thread.part[i], NULL);
		ft_putnbr(i); NL
	}*/
}

int	ft_mouse(int key, int x, int y, void *ptr)
{
	t_test *test = ptr;
	const int			s = test->sel_fra - 1;
	const double		tmpx = x / test->zoom + test->limx[s][0];
	const double		tmpy = y / test->zoom + test->limy[s][0];
//	const double		ecx = (fabs(test->limx[s][0] - test->limx[s][1])) / 2;
//	const double		ecy = (fabs(test->limy[s][0] - test->limy[s][1])) / 2;


	if (key == 1)
	{
		ft_putnbr(tmpx * 100); NL
		ft_putnbr(tmpy * 100); NL NL
		return (0);
	}
	else if (key == 2 && y > 0)
	{
		test->lock *= -1;
//		test->limx[s][0] = (tmpx - ecx);
//		test->limx[s][1] = (tmpx + ecx);
//		test->limy[s][0] = (tmpy - ecy);
//		test->limy[s][1] = (tmpy + ecy);
	}
	else if (key == 4 || key == 5)
	{
		test->zoom *= (1.25 * (1 - key % 2)) + (0.8 * (key % 2));
		test->limx[s][0] = test->limx[s][0] + (x - (WIDTH * 0.5 )) / test->zoom;
		test->limy[s][0] = test->limy[s][0] + (y - (HEIGHT * 0.5)) / test->zoom;
	}
	test_th(test);
	return (0);
}

int		set_val(t_test *test)
{
	test->zoom = 290;
	test->ite_max = 100;
	TIP.pos.x = 0;
	TIP.pos.y = 0;
	test->jc.r = 0.285;
	test->jc.i = 0.01;
	test->limy[0][0] = -1.2;
	test->limy[0][1] = 1.2;
	test->limx[0][0] = -2.1/* + j * 0.6*/;
	test->limx[0][1] = 0.6/* + j * 0.9*/;
	test->limy[1][0] = -1.2;
	test->limy[1][1] = 1.2;
	test->limx[1][0] = -2.1 + 0.6;
	test->limx[1][1] = 0.6 + 0.9;
	test->limy[2][0] = -2;
	test->limy[2][1] = 0.5;
	test->limx[2][0] = -2.1/* + j * 0.6*/;
	test->limx[2][1] = 0.6/* + j * 0.9*/;
	return (0);
}

int	ft_key(int key, void *ptr)
{
	t_test *test;

	test = ptr;
	if (key == 53)
		exit(1);
	if ((key == 123 && test->ite_max > 1) || (key == 124 && test->ite_max < 1000))
	{
		if (key == 123)
			test->ite_max -= (test->ite_max > 10 ? 10 : 1);
		else
			test->ite_max += (test->ite_max >= 10 ? 10 : 1);
	}
	else if (key == 0 || key == 2)
	{
		test->limx[test->sel_fra - 1][0] += 0.2 * (key - 1);
		test->limx[test->sel_fra - 1][1] += 0.2 * (key - 1);
	}
	else if (key == 13 || key == 1)
	{
		test->limy[test->sel_fra - 1][0] += 0.2 * (7 - key) / 6;
		test->limy[test->sel_fra - 1][1] += 0.2 * (7 - key) / 6;
	}
	else if (key == 36)
		set_val(test);
	else if ((key == 125 || key == 126)
			&& ((test->sel_fra += 2 * key - 251) + 1))
	{
		if (test->sel_fra % 4 == 0)
			test->sel_fra =  3 - test->sel_fra * 0.5;
		test->s = test->sel_fra - 1;
	}
	else if (key == 49)
		return (inf_call(test));
	test_th(test);
	return (0);
}

int		inf_call(void *ptr)
{
	 t_test *test;

	test = ptr;
//	mlx_clear_window(test->mlx_ptr, test->win_ptr);
	mlx_put_image_to_window(test->mlx_ptr, test->win_ptr,
		TIP.img_ptr, TIP.pos.y, TIP.pos.x);
	return (0);
}

void	*ftest(void *data)
{
	t_test *test;

	test = data;
	while (1)
	{
		pthread_mutex_lock(&test->thread.d_max);
		pthread_cond_wait(&test->thread.s_cond, &test->thread.d_max);
		test->keyt = NB_TH; TEST5
		pthread_cond_signal(&test->thread.v_cond);
		pthread_mutex_unlock(&test->thread.d_max);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_test	test;

	test.lock = -1;
	test.thread.d_max = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	test.thread.s_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	test.thread.v_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	test.keyt = NB_TH;
	set_val(&test);
	test.sel_fra = 1;
	if (ac == 2 && (!ft_strcmp("BS", av[1]) || !ft_strcmp("Julia", av[1])))
		test.sel_fra = 11 - av[1][0] / 8;
	test.mlx_ptr = mlx_init();
	test.win_ptr = mlx_new_window(test.mlx_ptr, WIDTH, HEIGHT, "test");
	TI.img_ptr = mlx_new_image	(test.mlx_ptr, WIDTH, HEIGHT);
	TI.data = mlx_get_data_addr(TI.img_ptr, &TI.bpp, &TI.sl, &TI.endian);
	pthread_create(&test.thread.stock, NULL, &ftest, &test);
	test_th(&test);
	mlx_hook(test.win_ptr, 2, 1, ft_key, &test);
	mlx_mouse_hook(test.win_ptr, ft_mouse, &test);
	mlx_loop_hook(test.mlx_ptr, inf_call, &test);
	mlx_hook(test.win_ptr, 6, 1L << 8, ft_tracking, &test);
	mlx_loop(test.mlx_ptr);
	return (0);
}
