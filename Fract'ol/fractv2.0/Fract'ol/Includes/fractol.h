/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 03:18:37 by jelusine          #+#    #+#             */
/*   Updated: 2018/11/25 07:49:13 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

# define WIDTH 16 * 50
# define HEIGHT 10 * 50
# define CHCOL 51
# define ERRMSG "Usage: fractol [Mandelbrot | Julia | Burning_Ship]\n"
# define TI test.img
# define TIP test->img
# define S test->s

typedef struct	s_point
{
	int		x;
	int		y;
	int		z;
}				t_point;

typedef struct	s_nima
{
	double		r;
	double		i;
}				t_nima;

typedef struct	s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		sl;
	int		endian;
	t_point	pos;
}				t_img;

typedef struct	s_test
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			lock;
	double		zoom[3];
	double		limxy[3][2];
	int			ite_max[3];
	int			s;
	t_nima		jc;
	t_img		img[3];
}				t_test;

int				ft_mouse(int key, int x, int y, void *ptr);
int				ft_tracking(int x, int y, void *ptr);
int				ft_key(int key, void *ptr);
int				fractest(void *data, int k);
void			set_val(t_test *test);

#endif
