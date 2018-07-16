/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:12:30 by jelusine          #+#    #+#             */
/*   Updated: 2018/07/08 17:59:33 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# define WIDTH 15 * PIX * 5
# define HEIGHT 9 * PIX * 5
# define ECART 20
# define PIX 23
# define CST 0.2
# define CST2 0.2
# define TAB test.grid->tab
# define TABP test->grid->tab
# define TI test.img
# define TIP test->img

typedef struct	s_pointa
{
	int	x;
	int	y;
//	int	z;
}				t_pointa;

typedef struct	s_point
{
	int		x;
	int		y;
	int		z;
	float		xa;
	float		ya;
	t_pointa	p;
	t_pointa	pa;
}				t_point;

typedef struct	s_gridpnt
{
	int		lenx;
	int		leny;
	float	zc;
	float	min;
	float	cstc;
	t_point	**tab;
}				t_gridpnt;

typedef struct	s_img
{
	void		*img_ptr;
	char		*data;
	int			bpp;
	int			sl;
	int			endian;
	t_pointa	ref;
	int			pos[2];
	int			posx;
	int			posy;
	int			width;
	int			height;
}				t_img;

typedef struct	s_test
{
	int			lock;
	int			lockx;
	int			locky;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_gridpnt	*grid;
}				t_test;

t_gridpnt		*ft_osef(t_list *lst, int lenx, int leny);
t_gridpnt		*ft_parser(char *path);
int				ptit_test(void *ptr);
int				pseudo_fdf(int key, void *ptr);
void			ft_paintashier(int key, int x, int y, void *ptr, int *k);
void			ft_set_npoint(t_test *test, float z, float cst);
void			ft_affiche_point(t_test test);
void			trace_ligne(/*t_pointa a, t_pointa b*/int xa, int ya, int xb, int yb, void *ptr, int col, int i);
int				pseudo_snake(int key, void *ptr);
int				ft_polygone(int key, int x, int y, void *ptr);
void			ft_tracecrox(int x, int y, void *ptr, int color);

#endif
