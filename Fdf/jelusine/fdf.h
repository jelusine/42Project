/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:12:30 by jelusine          #+#    #+#             */
/*   Updated: 2018/09/11 01:52:43 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# define CHCOL 51
# define WIDTH 15 * PIX * 5
# define HEIGHT 9 * PIX * 5
# define ECART 20
# define PIX 23
# define CST 0.2
# define CST2 0.2
# define TLOCK test->lock
# define TAB test.grid->tab
# define TABP test->grid->tab
# define TI test.img
# define TIP test->img
# define TGP test->grid

typedef struct	s_pointa
{
	int	x;
	int	y;
	int	z;
}				t_pointa;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			a[2];
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
	int			wihei[2];
	long		col[2];
}				t_img;

typedef struct	s_test
{
	int			lock;
	int			lockx;
	int			locky;
	int			pzoom;
	int			lola[2];
	int			bold;
	void		*mlx_ptr;
	void		*win_ptr;
	double		lim;
	double		limmin;
	t_img		img;
	t_gridpnt	*grid;
}				t_test;

t_gridpnt		*ft_parser(char *path, t_test *test);
int				ptit_test(void *ptr);
int				ft_exit(int key, void *ptr);
int				ft_affiche_point(t_test test);
int				pseudo_fdf(int key, void *ptr);
int				pseudo_snake(int key, void *ptr);
int				ft_change_color(long *col, int i);
int				ft_set_map(void *ptr, char *path);
int				ft_polygone(int key, int x, int y, void *ptr);
int				ft_set_npoint(t_test *test, float z, float cst);
void			ft_sample(const t_test *test);
void			del(void *content, size_t size);
void			trace_ligne(int a[2], const int b[2], void *ptr, int i);
void			ft_tracecrox(int pnt[2], void *ptr, int color, int bold);
void			ft_paintashier(int key, const int coor[2],
										t_test *test, int *k);

#endif
