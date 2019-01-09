/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fncpf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 02:10:00 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/09 05:54:06 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	pfs->pad--;
	pfs->len += ft_max(pfs->pad, 0) + 1;
	if (!(pfs->key & 0x08) && pfs->pad > -1)
	{
		while (pfs->pad-- > 0)
			ft_putchar(32 + (pfs->key & 0x40) / 4);
	}
	ft_putchar(c);
	while (pfs->pad-- > 0)
		ft_putchar(' ');
}

void	fnc_str(t_pfs *pfs)
{
	char 	*s;
	int		l;

	if (!(s = va_arg(pfs->ap, typeof(s))) && (pfs->len += 6))
		return (ft_putstr("(null)"));
	if ((l = ft_strlen(s)) > pfs->prec && pfs->prec >= 0)
		l = pfs->prec;
	pfs->pad -= l;
	pfs->len += l + ft_max(pfs->pad, 0);
	if (!(pfs->key & 0x08) && pfs->pad > -1)
	{
		while (pfs->pad-- > 0)
			ft_putchar(32 + (pfs->key & 0x40) / 4);
	}
	write(1, s, l);
	while (pfs->pad-- > 0)
		ft_putchar(' ');
}

void	fnc_int(t_pfs *pfs)
{
	int d;

	if (((d = va_arg(pfs->ap, typeof(d))) < 0 || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
	pfs->pad -= ft_max(pfs->prec, ft_nb_len(d, 10)) - (!(pfs->prec || d) && pfs->pad > 0 ? 1 : 0);
	pfs->len += ft_max(pfs->prec, ft_nb_len(d, 10)) + ft_max(pfs->pad, 0) - 1;
	if (!(pfs->key & 0x48) && pfs->pad > -1)
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (pfs->key & 0x30 && d >= 0)
		ft_putchar(21 + (pfs->key & 0x30) * 11 / 16);
	if (pfs->prec > 0 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		pfs->prec -= ft_nb_len(d, 10);
		if (pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		if (d < 0 && (d *= -1))
			ft_putchar('-');
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
	if ((pfs->prec || d) && ++pfs->len)
		ft_putnbr(d);
	while (pfs->pad-- > 0)
		ft_putchar(' ');
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
	unsigned int u;

	u = va_arg(pfs->ap, typeof(u));
	pfs->pad -= ft_max(pfs->prec, ft_unb_len(u, 10))
		- (!(pfs->prec || u) && pfs->pad > 0 ? 1 : 0);
	pfs->len += ft_max(pfs->pad, 0) + ft_max(pfs->prec, ft_unb_len(u, 10)) - 1;
	if (!(pfs->key & 0x48) && pfs->pad > -1)
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (pfs->prec > 0 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		pfs->prec -= ft_unb_len(u, 10);
		if (pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
	if ((pfs->prec || u) && ++pfs->len)
		ft_putinfnbr(u);
	while (pfs->pad-- > 0)
		ft_putchar(' ');
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
	while (pfs->pad-- > 0)
		ft_putchar(' ');
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
//	if (l && !(l % 100000000))
//		ft_putstr("00000000");
	else
		ft_putnbr_base(l % 100000000, base);
}

void	fnc_oct(t_pfs *pfs)
{
	unsigned int o;

	if ((o = va_arg(pfs->ap, typeof(o))) && pfs->key & 0x80)
		pfs->pad--;
	pfs->pad -= ft_max(pfs->prec, ft_unb_len(o, 8)) - (!(pfs->prec || o) && pfs->pad > 0 ? 1 : 0);
	pfs->len += ft_max(pfs->prec, ft_unb_len(o, 8)) + ft_max(pfs->pad, 0) - 1;
	if (!(pfs->key & 0x48) && pfs->pad)
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (o && pfs->key & 0x80 && (++pfs->len))
		ft_putchar('0');
	if (pfs->prec > 0 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		pfs->prec -= ft_unb_len(o, 8);
		if (pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
	if ((pfs->prec || o || pfs->key & 0x80) && ++pfs->len)
		ft_putnbr_base(o, "01234567");
	while (pfs->pad-- > 0)
		ft_putchar(' ');
}

void	fnc_hexa(t_pfs *pfs, int i)
{
	unsigned int			h;
	static const char	*str[4] = {HEXAU, HEXAL, "0X", "0x"};

	if ((h = va_arg(pfs->ap, typeof(h))) && pfs->key & 0x80)
		pfs->pad -= 2;
	pfs->pad -= ft_max(pfs->prec, ft_unb_len(h, 16)) - (!(pfs->prec || h) && pfs->pad > 0 ? 1 : 0);
	pfs->len += ft_max(pfs->prec, ft_unb_len(h, 16)) + ft_max(pfs->pad, 0) - 1;
	if (!(pfs->key & 0x48) && pfs->pad)
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (h && pfs->key & 0x80 && (pfs->len += 2))
		write(1, str[i + 2], 2);
	if (pfs->prec > 0 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		pfs->prec -= ft_unb_len(h, 16);
		if (pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
	if ((pfs->prec || h) && ++pfs->len)
		ft_putnbr_base(h, str[i]);
	while (pfs->pad-- > 0)
		ft_putchar(' ');
}

void	fnc_unsbas(t_pfs *pfs, int i)
{
	unsigned int u;
	static const char	*str[4] = {"0123456789ABCDEF", "0123456789abcdef",
		"0X", "0x"};

	u = va_arg(pfs->ap, typeof(u));
	if (pfs->key & 0x80)
		write(1, str[i + 2], 2);
	ft_putnbr_base(u, str[i]);
}
