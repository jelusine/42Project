/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fract'ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 03:18:37 by jelusine          #+#    #+#             */
/*   Updated: 2018/10/10 17:29:19 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>

# define WIDTH 16 * 50
# define HEIGHT 10 * 50
# define CHCOL 51
# define NB_TH 8
# define WID_DIV WIDTH / NB_TH
# define HEI_DIV HEIGHT / (NB_TH * 4)
# define TI test.img
# define TIP test->img

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

typedef struct	s_thread
{
	pthread_t		stock;
	pthread_t		part[NB_TH];
	pthread_cond_t	s_cond;
	pthread_cond_t	v_cond;
	pthread_mutex_t	d_max;
}				t_thread;

typedef struct	s_test
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			ite_max;
	int			lock;
	double		zoom;
	double		limy[3][2];
	double		limx[3][2];
	int			sel_fra;
	int			s;
	int			d_max;
	int			keyt;
	int			kyt;
	t_nima		jc;
	t_thread	thread;
	t_img		img;
}				t_test;

int		ft_change_color(long *col, int i);
int		ft_mouse(int key, int x, int y, void *ptr);
int		ft_tracking(int x, int y, void *ptr);
int		inf_call(void *ptr);

#endif
