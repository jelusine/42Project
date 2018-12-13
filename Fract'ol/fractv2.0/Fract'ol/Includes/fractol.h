/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 03:18:37 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/03 08:51:14 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

# define WIDTH 16 * 50
# define HEIGHT 10 * 50
# define ERRMSG "Usage: fractol [Mandelbrot, Julia, Burning_Ship, Multibrot]\n"
# define TFP test->frac
# define SAVE test->save
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

typedef struct	s_frac
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		sl;
	int		endian;
	double	zoom;
	double	limxy[2];
	int		ite_max;
	int		n;
}				t_frac;

typedef struct	s_test
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			lock;
	int			s;
	int			save;
	void		(*f)(double *, double *, t_nima, int);
	t_nima		jc;
	t_frac		frac[2];
}				t_test;

int				ft_mouse(int key, int x, int y, void *ptr);
int				ft_tracking(int x, int y, void *ptr);
int				ft_key(int key, void *ptr);
int				fractest(t_test *test, int k, int s);
void			set_val(t_test *test, int s, int k);
void			frac_mandeljul(double *r, double *i, t_nima cst, int n);
void			frac_multibrot(double *r, double *i, t_nima cst, int n);
void			frac_burning_ship(double *r, double *i, t_nima cst, int n);

#endif
