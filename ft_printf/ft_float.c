/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 06:57:07 by jelusine          #+#    #+#             */
/*   Updated: 2019/03/05 08:02:48 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

double		ft_pow(int n, int p)
{
	double	nb;
	int		np;

	nb = 1;
	np = ft_abs(p);
	while (np-- > 0)
		nb *= n;
	return ((p < 0 ? 1 / nb : nb));
}

void		fnc_float(t_pfs *pfs)
{
	double	f;
	double	ff;
	char	*str;
	int		k;
	int		p;
	int		t;

	f = va_arg(pfs->ap, typeof(f));
	if (pfs->prec < 0)
		pfs->prec = 6;
	if (pfs->prec)
	{
		t = ++pfs->prec + 1;
		ff = f;
		while (--t > 0)
			ff = (ff - (long)ff) * 10;
		if ((int)ff % 10 >= 5 || -1 >= (int)ff % 10)
			f += ft_pow(10, -(pfs->prec - 1)) * (f > 0 ? 1 : -1);
	}
	str = ft_itoa_base(f, 10);
	k = ft_strlen(str);
	if (!(pfs->str = (char *)malloc(sizeof(char) * (k + pfs->prec + 1))))
		return ;
	ft_strcpy(pfs->str, str);
	ft_strdel(&str);
	pfs->str[k] = '.';
	if (f < 0)
		f *= -1;
	p = 1;
	while (--pfs->prec > 0)
	{
		f = (f - (long)f) * 10;
		pfs->str[k + p++] = 48 + ft_abs((int)f) % 10;
	}
	pfs->str[k + (p == 1 ? 0 : p)] = 0;
	pfs->strlen = ft_strlen(pfs->str);
	if ((pfs->str[0] == '-' || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
}
