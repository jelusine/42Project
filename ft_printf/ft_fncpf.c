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
	char c;

	c = va_arg(pfs->ap, int);
	pfs->str = ft_strdup("0");
	pfs->str[0] = c;
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
//	pfs->pad -= pfs->strlen;
//	pfs->len += pfs->strlen + ft_max(pfs->pad,  0);
}

void	fnc_int(t_pfs *pfs)
{
	long int d;

	d = va_arg(pfs->ap, typeof(d));
//	free(pfs->str);
	if ((pfs->key & 0x03) == 3)
		pfs->str = ft_itoa_base((char)d, 10);
	else if (pfs->key & 0x02)
		pfs->str = ft_itoa_base((short int)d, 10);
	else if (pfs->key & 0x04)
		pfs->str = ft_itoa_base(d, 10);
	else
		pfs->str = ft_itoa_base((int)d, 10);
	pfs->strlen = ft_strlen(pfs->str);
	if ((pfs->str[0] == '-' || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
}

void	ft_putinfnbr(long long int l)
{
	if (l < 0)
	{
		ft_putchar('-');
		l *= -1;
	}
	if (l >= 100000000)
		ft_putinfnbr(l / 100000000);
	if (l && !(l % 100000000))
		ft_putstr("00000000");
	else
		ft_putnbr(l % 100000000);
}

void	fnc_uint(t_pfs *pfs)
{
	unsigned long int u;

	u = va_arg(pfs->ap, typeof(u));
	if ((pfs->key & 0x03) == 3)
		pfs->str = ft_utoa_base((unsigned char)u, 10);
	else if (pfs->key & 0x02)
		pfs->str = ft_utoa_base((unsigned short int)u, 10);
	else if (pfs->key & 0x04)
		pfs->str = ft_utoa_base(u, 10);
	else
		pfs->str = ft_utoa_base((unsigned int)u, 10);
	pfs->strlen = ft_strlen(pfs->str);
	//ft_putstr(pfs->str);
	//ft_putnbr((pfs->strlen = ft_strlen(pfs->str))); //TEST2
}

void	fnc_long(t_pfs *pfs)
{
	long l;

	if (((l = va_arg(pfs->ap, typeof(l))) < 0 || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
	pfs->pad -= ft_max(pfs->prec, ft_nb_len(l, 10)) - (!(pfs->prec || l) && pfs->pad > 0 ? 1 : 0);
	pfs->len += ft_max(pfs->pad, 0) + ft_max(pfs->prec, ft_nb_len(l, 10)) - 1;
	if (!(pfs->key & 0x48) && pfs->pad > -1)
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (pfs->key & 0x30 && l >= 0)
		ft_putchar(21 + (pfs->key & 0x30) * 11 / 16);
	if (pfs->prec > 0 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		pfs->prec -= ft_nb_len(l, 10);
		if (pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		if (l < 0 && (l *= -1))
			ft_putchar('-');
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
	if ((pfs->prec || l) && ++pfs->len)
		ft_putinfnbr(l);
}

void	ft_putinfnbr_base(long long int l, char *base)
{
	if (l < 0)
	{
		ft_putchar('-');
		l *= -1;
	}
	if (l >= 100000000)
		ft_putinfnbr_base(l / 100000000, base);
	if (l && !(l % 100000000))
		ft_putstr("00000000");
	else
		ft_putnbr_base(l % 100000000, base);
}

void	fnc_oct(t_pfs *pfs)
{
	unsigned long o;

	if ((o = va_arg(pfs->ap, typeof(o))) && pfs->key & 0x80)
		pfs->pad--;
	if ((pfs->key & 0x03) == 3)
		pfs->str = ft_itoa_base((unsigned char)o, 8);
	else if (pfs->key & 0x02)
			pfs->str = ft_itoa_base((unsigned short int)o, 8);
	else if (pfs->key & 0x04)
		pfs->str = ft_itoa_base(o, 8);
	else
		pfs->str = ft_itoa_base((unsigned int)o, 8);
	pfs->strlen = ft_strlen(pfs->str);
}

void	fnc_hexa(t_pfs *pfs)
{
	unsigned	long	h;

	if ((h = va_arg(pfs->ap, typeof(h))) && pfs->key & 0x80)
		pfs->pad -= 2;
	if ((pfs->key & 0x03) == 3)
		pfs->str = ft_itoa_base((unsigned char)h, 16);
	else if (pfs->key & 0x02)
			pfs->str = ft_itoa_base((unsigned short int)h, 16);
	else if (pfs->key & 0x04)
		pfs->str = ft_itoa_base(h, 16);
	else
		pfs->str = ft_itoa_base((unsigned int)h, 16);
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
	while (--pfs->prec > 0 && (x *= 10))
		pfs->str[k + p++] = 48 + ft_abs((int)(f * x)) % 10;
	pfs->str[k + (p == 1 ? 0 : p)] = 0;
	pfs->strlen = ft_strlen(pfs->str);
	if ((pfs->str[0] == '-' || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
}
