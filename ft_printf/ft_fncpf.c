/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fncpf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 02:10:00 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/22 21:29:55 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_utoa_base(unsigned long nb, unsigned int tbse)
{
	char		*str;
	unsigned long		i;
	int			n;
	const char	*base = "0123456789ABCDEF";

	if (tbse < 2 || 16 < tbse)
		return (0);
	n = 1;
	i = nb;
	while (i >= tbse && ++n)
		i /= tbse;
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	str[n--] = '\0';
	str[0] = '0';
	i = nb;
	while (i >= 1)
	{
		str[n--] = base[i % tbse];
		i /= tbse;
	}
	return (str);
}

int		ft_unb_len(unsigned int nb, unsigned int base)
{
	int	i;

	i = 1;
	while (base <= nb && ++i)
		nb /= base;
	return (i);
}

void	fnc_char(t_pfs *pfs)
{
	pfs->str = ft_strdup("0");
	pfs->str[0] = va_arg(pfs->ap, int);
	pfs->strlen = 1;
	pfs->prec = -1;
}

void	fnc_str(t_pfs *pfs)
{
	char *s;

	pfs->str = ft_strdup("");
	if (!(s = va_arg(pfs->ap, char*)) && (pfs->len += 6))
		return (ft_putstr("(null)"));
	if ((pfs->strlen = ft_strlen(s)) > pfs->prec && pfs->prec >= 0)
		pfs->strlen = pfs->prec;
	pfs->prec = -1;
	ft_strdel(&pfs->str);
	pfs->str = ft_strdup(s);
}

void	fnc_int(t_pfs *pfs)
{
	long long int d;

	d = va_arg(pfs->ap, typeof(d));
	if ((pfs->key & 0x03) == 3)
		pfs->str = ft_itoa_base((char)d, 10);
	else if ((pfs->key & 0x05) == 5)
		pfs->str = ft_itoa_base(d, 10);
	else if (pfs->key & 0x02)
		pfs->str = ft_itoa_base((short int)d, 10);
	else if (pfs->key & 0x04)
		pfs->str = ft_itoa_base((long)d, 10);
	else
		pfs->str = ft_itoa_base((int)d, 10);
	pfs->strlen = ft_strlen(pfs->str);
	if ((pfs->str[0] == '-' || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
}

void	fnc_uint(t_pfs *pfs)
{
	unsigned long long int u;

	u = va_arg(pfs->ap, typeof(u));
	if ((pfs->key & 0x03) == 3)
		pfs->str = ft_utoa_base((unsigned char)u, 10);
	else if ((pfs->key & 0x05) == 5)
		pfs->str = ft_utoa_base(u, 10);
	else if (pfs->key & 0x02)
		pfs->str = ft_utoa_base((unsigned short int)u, 10);
	else if (pfs->key & 0x04)
		pfs->str = ft_utoa_base((unsigned long)u, 10);
	else
		pfs->str = ft_utoa_base((unsigned int)u, 10);
	pfs->strlen = ft_strlen(pfs->str);
}

void	fnc_oct(t_pfs *pfs)
{
	unsigned long long int o;

	if ((o = va_arg(pfs->ap, typeof(o))) && pfs->key & 0x80)
		pfs->pad -= (pfs->type & 0x0c) / 4;
	if ((pfs->key & 0x03) == 3)
		pfs->str = ft_itoa_base((unsigned char)o, 2 * (pfs->type & 0x0c));
	else if ((pfs->key & 0x05) == 5)
		pfs->str = ft_itoa_base(o, 2 * (pfs->type & 0x0c));
	else if (pfs->key & 0x02)
			pfs->str = ft_itoa_base((unsigned short int)o, 2 * (pfs->type & 0x0c));
	else if (pfs->key & 0x04)
		pfs->str = ft_itoa_base((unsigned long int)o, 2 * (pfs->type & 0x0c));
	else
		pfs->str = ft_itoa_base((unsigned int)o, 2 * (pfs->type & 0x0c));
	pfs->strlen = ft_strlen(pfs->str);
}

void fnc_float(t_pfs *pfs)
{
	double 	f;
	char		*str;
	int			k;
	int 		p;
	unsigned int			x;

	f = va_arg(pfs->ap, typeof(f));
	str = ft_itoa_base(f, 10);
	k = ft_strlen(str);
 	if (pfs->prec < 0)
		pfs->prec = 6;
	if (pfs->prec)
		pfs->prec++;
	if (!(pfs->str = (char *)malloc(sizeof(char) * (k + pfs->prec + 1))))
		return ;
	ft_strcpy(pfs->str, str);
	ft_strdel(&str);
	pfs->str[k] = '.';
	if (f < 0)
		f *= -1;
	p = 1;
	x = 1;
	//f -= (long int)f;
	while (--pfs->prec > 0/* && (x *= 10)*/)
	{
		f = (f - (long)f) * 10;
		pfs->str[k + p++] = 48 + ft_abs((int)(f/* * x*/)) % 10;
	}
	pfs->str[k + (p == 1 ? 0 : p)] = 0;
	pfs->strlen = ft_strlen(pfs->str);
	if ((pfs->str[0] == '-' || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
}
