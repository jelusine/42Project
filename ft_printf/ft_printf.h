/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 02:35:07 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/12 12:02:03 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <math.h>
# define FTEST 0.999990
# define HEXAL "0123456789abcdef"
# define HEXAU "0123456789ABCDEF"
# define SETCOL "red\0green\0yellow\0blue\0purple\0cyan\0white\0eoc"

typedef struct	s_dbl
{
	unsigned int 	manta	: 16;
	unsigned int 	mantb	: 16;
	unsigned int 	mantc	: 16;
	unsigned int 	mantd	: 4;
	unsigned int 	exp		: 11;
	unsigned int 	sign	: 1;
}								t_dbl;

typedef struct	s_flt
{
	unsigned int 	manta	: 16;
	unsigned int 	mantb	: 7;
	unsigned int 	exp		: 8;
	unsigned int 	sign	: 1;
}								t_flt;

typedef struct	s_pfs
{
	va_list			ap;
	unsigned int	key;
	unsigned int	type;
	int				prec;
	int				pad;
	int				len;
	char			*str;
	int				strlen;
}								t_pfs;

void			fnc_char(t_pfs *pfs);
void			fnc_int(t_pfs *pfs);
void			fnc_uint(t_pfs *pfs);
void			ft_putinfnbr(long long int l);
void			ft_putinfnbr_base(long long int l, char *base);
void			fnc_long(t_pfs *pfs);
void			fnc_str(t_pfs *pfs);
void			fnc_oct(t_pfs *pfs);
void 			fnc_float(t_pfs *pfs);
void			fnc_unsbas(t_pfs *pfs, int i);
int 		  ft_pfcolor(const char *str, int *pflen);
int				ft_nb_len(long nb, int base);
int				ft_printf(char *fmt, ...);
double		ft_pow(int n, int p);

#endif
