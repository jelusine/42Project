/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fncpf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 02:10:00 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/06 02:57:54 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fnc_char(t_pfs *pfs)
{
	char c;

	c = va_arg(pfs->ap, int);
	ft_putchar(c);
}

void	fnc_str(t_pfs *pfs)
{
	char 	*s;
	int		l;

	s = va_arg(pfs->ap, typeof(s));
	if ((l = ft_strlen(s)) > pfs->prec && pfs->prec >= 0)
		l = pfs->prec;
	pfs->pad -= l;
	pfs->len += l + ft_max(pfs->pad, 0);
	if (!(pfs->key & 0x08) && pfs->pad > -1)
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	write(1, s, l);
	while (pfs->pad-- > 0)
		ft_putchar(' ');
}

void	fnc_int(t_pfs *pfs)
{
	int d;

	d = va_arg(pfs->ap, typeof(d));
	if ((d < 0 || pfs->key & 0x30) && ++pfs->len)
		pfs->pad--;
	pfs->pad -= ft_max(pfs->prec, ft_nb_len(d, 10));
	pfs->len += ft_max(pfs->pad, 0) + ft_max(pfs->prec, ft_nb_len(d, 10)) - 1;
	if (!(pfs->key & 0x48) && pfs->pad > -1)
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (pfs->key & 0x30 && d >= 0)
		ft_putchar(21 + (pfs->key & 0x30) * 11 / 16);
	if (pfs->prec > -1 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		pfs->prec -= ft_nb_len(d, 10);
		if (pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		if (d < 0 && (d *= -1))
			ft_putchar('-');
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
	if (pfs->prec != 0 && ++pfs->len)
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

void	fnc_long(t_pfs *pfs)
{
	long	d;
	int 	n;

	d = va_arg(pfs->ap, long);
	if ((pfs->key & 0x20) && d > 0)
		ft_putchar('+');
	if (pfs->prec)
	{
		n = pfs->prec - ft_nb_len(d, 10);
		while (n-- > 0)
			ft_putchar('0');
	}
	ft_putinfnbr(d);
}

void	fnc_oct(t_pfs *pfs)
{
	int o;
	int n;

	o = va_arg(pfs->ap, int);
	if (pfs->key & 0x80)
		ft_putchar('0');
	if (pfs->prec)
	{
		n = pfs->prec - ft_nb_len(o, 8);
		while (n-- > 0)
			ft_putchar('0');
	}
	ft_putnbr_base(o, "01234567");
}

void	fnc_lhexa(t_pfs *pfs)
{
	int h;

	h = va_arg(pfs->ap, long);
	if (pfs->key & 0x80)
		ft_putchar('0');
	ft_putinfnbr_base(h, "0123456789abcdef");
}

void	fnc_hexa(t_pfs *pfs, int i)
{
	unsigned int			h;
	static const char	*str[4] = {"0123456789ABCDEF", "0123456789abcdef",
		"0X", "0x"};

	if ((h = va_arg(pfs->ap, typeof(h))) && pfs->key & 0x80)
		pfs->pad -= 2;
	pfs->pad -= ft_max(pfs->prec, ft_nb_len(h, 16));
	pfs->len += ft_max(pfs->prec, ft_nb_len(h, 16)) + ft_max(pfs->pad, 0);
	if (!(pfs->key & 0x40) && pfs->pad && !(pfs->key & 0x08))
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (h && pfs->key & 0x80 && (pfs->len += 2))
		write(1, str[i + 2], 2);
	if (pfs->prec > -1 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		pfs->prec -= ft_nb_len(h, 16);
		if (pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
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
