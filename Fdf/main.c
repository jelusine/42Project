/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:11:50 by jelusine          #+#    #+#             */
/*   Updated: 2018/07/15 21:02:41 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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
//	ft_putnbr(y); NL
//	ft_putnbr(x); NL NL
	test->img.data[y * test->img.sl + x * test->img.bpp / 8] = b;
	test->img.data[y * test->img.sl + x * test->img.bpp / 8 + 1] = r;
	test->img.data[y * test->img.sl + x * test->img.bpp / 8 + 2] = g;
}


void	trace_ligne(/*t_pointa a, t_pointa b*/int xa, int ya, int xb, int yb, void *ptr, int col, int i)
{
	int dx;
	int dy;
	int	dp;
	int de;
	int dne;
	const t_test	*test = ptr;

	if (xa > xb)
	{
		ft_swap(&xa, &xb);
		ft_swap(&ya, &yb);
	}
	if (i == 0)
		col = mlx_get_color_value(test->mlx_ptr, col);
	dx = xb - xa;
	dy = ft_abs(yb - ya);
	dp = 2 * ft_min(dx, dy) - ft_max(dx, dy);
	de = 2 * ft_min(dx, dy);
	dne = -2 * ft_abs(dy - dx);
	while (xa <= xb || ya != yb)
	{
/*		TEST2 NL
		ft_putnbr(ya * 10); NL
		ft_putnbr(xa * 10); NL
		ft_putnbr(yb * 10); NL
		ft_putnbr(xb * 10); NL
		TEST4 NL*/
		if (dp > 0 || (dp <= 0 && dx >= dy))
			xa++;
		if (dp > 0 || (dp <= 0 && dx < dy))
			ya += (yb - ya > 0 ? 1 : -1);
		dp += (dp <= 0 ? de : dne);
		if (i == 1)
			mlx_pixel_put(test->mlx_ptr, test->win_ptr, xa, ya, col);
		else
			pix_img(ptr, ya, xa, col);
		if (xa == xb && ya == yb)
			break ;
	}
}

/*void	trace_ligne(int xa, int ya, int xb, int yb, void *ptr)
{
	int dx;
	int dy;
	int e;
	t_test *test;

	test = ptr;
	e = xb - xa;
	dx = 2 * e;
	dy = (yb - ya) * 2;
	while (xa <= xb)
	{
		mlx_pixel_put(test->mlx_ptr, test->win_ptr, xa, ya, 0xffffff);
		xa++;
		if ((e = e - dy) <= 0)
		{
			ya++;
			e = e + dx;
		}
	}
}*/


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
	else if (key == 4 || (key == 5 && TIP.width >= TIP.height))
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

	if (key == 91 || (key == 84 && TIP.width >= TIP.height))
		ft_set_npoint(test, 0, -1 * pow(-1, key % 2));
	else if (key == 69 || key == 78)
	{
		tmp = floor(TABP[(int)TIP.ref.y][(int)TIP.ref.x].ya);
		ft_set_npoint(test, -0.5 * pow(-1, key % 2), 0);
		TIP.pos[1] -= floor(TABP[(int)TIP.ref.y][(int)TIP.ref.x].ya) - tmp;
	}
	else if (key == 36)
	{
		test->lock = -1;
		test->img.pos[0] = 0;
		test->img.pos[1] = 0;
		ft_set_npoint(test, -test->grid->zc, -test->grid->cstc + CST2);
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
								0, 1, 2, 13, 91, 84, 69, 78, 36};

	test = ptr;
	if (key == 53)
		exit(1);
	if (key == 117)
		return (mlx_clear_window(test->mlx_ptr, test->win_ptr));
	i = 0;
	while (i < 16 && keyset[i] != key)
		i++;
	if (i < 16)
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
	t_test	*test = ptr;

	if (test->lock > 0)
	{
		if (test->lock % 2 == 0)
			mlx_pixel_put(test->mlx_ptr, test->win_ptr, x, y , 0xffff00);
		else
		{
			TIP.pos[0] = x - test->lockx;
			TIP.pos[1] = y - test->locky;
		}
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
	if (ac == 2)
	{
		TI.pos[0] = 0;
		TI.pos[1] = 0;
		TI.ref.x = ++test.lock;
		if (!(test.grid = ft_parser(av[1])))
		{
			ft_putendl("Error map !");
			return (0);
		}
		ft_set_npoint(&test, 0, 0);
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
