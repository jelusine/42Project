/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 05:04:17 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/12 09:45:48 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		ft_nb_len(long nb, int base)
{
	int i;

	i = 1;
	while ((nb <= -base || base <= nb) && ++i)
		nb /= base;
	return (i);
}

int		ft_parsing(char *str, t_pfs *pfs)
{
	int i;
	int n;

	i = 1;
	while (str[i] && ft_charcmpstr(str[i], "cspdiouxXfF") < 0)
		i++;
	n = 0;
	while (++n < i)
	{
		if (str[n] == '#')
			pfs->key = pfs->key | 0x80;
		else if (ft_isdigit(str[n]) && str[n - 1] != '.' && !ft_isdigit(str[n - 1]))
		{
			if (str[n] == '0' && !(pfs->key & 0x08))
				pfs->key = pfs->key | 0x40;
			pfs->pad = ft_atoi(&str[n]);
			n += ft_nb_len(pfs->pad, 10) - 1;
		}
		else if (str[n] == '+')
		{
			pfs->key = pfs->key | 0x20;
			pfs->key = pfs->key & 0xef;
		}
		else if (!(pfs->key & 0x20) && str[n] == ' ')
			pfs->key = pfs->key | 0x10;
		else if (str[n] == '-')
		{
			pfs->key = pfs->key | 0x08;
			pfs->key = pfs->key & 0xbf;
		}
		else if (!(pfs->key & 0x04) && str[n] == 'l')
		{
			pfs->key = pfs->key | 0x04;
			pfs->key = pfs->key & 0xfc;
			if (str[n + 1] == 'l')
				pfs->key = pfs->key | 0x01;
		}
		else if (!(pfs->key & 0x04) && str[n] == 'h')
		{
			pfs->key = pfs->key | 0x02;
			if (str[n + 1] == 'h')
				pfs->key = pfs->key | 0x01;
		}
		else if (str[n] == '.')
			pfs->prec = ft_atoi(&str[n + 1]);
	}
	if (str[i] == 'c')
		fnc_char(pfs);
	else if (str[i] == 's')
		fnc_str(pfs);
	else if (str[i] == 'u' && (pfs->type = pfs->type | 0x02))
		fnc_uint(pfs);
	else if ((str[i] == 'd' || str[i] == 'i') && (pfs->type = pfs->type | 0x01))
		fnc_int(pfs);
	else if (str[i] == 'o' && (pfs->type = pfs->type | 0x04))
		fnc_oct(pfs);
	else if ((str[i] == 'x' || str[i] == 'X') && (pfs->type = pfs->type | 0x08))
		fnc_hexa(pfs);
	else if (str[i] == 'f' && (pfs->type = pfs->type | 0x01))
		fnc_float(pfs);
	pfs->pad -= ft_max(pfs->prec, pfs->strlen - (pfs->str[0] == '-' && pfs->type & 0x0f ? 1 : 0)) - (!(pfs->prec || pfs->str[0] != '0') && pfs->pad > 0 ? 1 : 0);
	pfs->len += ft_max(pfs->prec, pfs->strlen - (pfs->str[0] == '-' && pfs->type & 0x0f ? 1 : 0)) + ft_max(pfs->pad, 0) - 1;
	if (pfs->pad > -1 && !(pfs->key & 0x08) && (!(pfs->key & 0x40) || (pfs->prec >= 0 && pfs->key & 0x40 && pfs->type & 0x0f)))
	{
		while (pfs->pad-- > 0)
			ft_putchar(' ');
	}
	if (pfs->type & 0x01 && pfs->key & 0x30 && pfs->str[0] != '-')
		ft_putchar(21 + (pfs->key & 0x30) * 11 / 16);
	if (pfs->type & 0x0c && pfs->str[0] != '0' && pfs->key & 0x80 && (pfs->len += (pfs->type & 0x0c) / 4))
		write(1, (str[i] == 'x' ? "0x" : "0X"), (pfs->type & 0x0c) / 4);
	if (pfs->prec > 0 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		if (pfs->str[0] == '-' && ++pfs->str && pfs->strlen--)
			ft_putchar('-');
		pfs->prec -= pfs->strlen;
		if (pfs->prec < 0 && pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		while (pfs->prec-- > 0)
			ft_putchar('0');
	}
	n = -1;
	while (str[i] == 'x' && pfs->str[++n])
		pfs->str[n] = ft_tolower(pfs->str[n]);
	if ((pfs->prec || pfs->str[0] != '0' || (pfs->key & 0x80 && pfs->type & 0x04)) && ++pfs->len)
		write(1, pfs->str, pfs->strlen);
	while (pfs->pad-- > 0)
		ft_putchar(' ');
	return (i + 1);
}

int		ft_printf(char *fmt, ...)
{
	t_pfs	pfs;
	va_list	ap;
	int		s;
	int		e;

	pfs.key = 0;
	pfs.type = 0;
	va_start(pfs.ap, fmt);
	s = 0;
	e = -1;
	pfs.prec = -1;
	pfs.pad = -1;
	pfs.len = 0;
	pfs.strlen = 0;
	while (fmt[++e])
	{
		if (fmt[e] == '%')
		{
			write(1, &fmt[s], e - s);
			if (fmt[e + 1] != '%')
			{
				pfs.len += e - s;
				pfs.str = ft_strdup("");
				s = e + ft_parsing(&fmt[e], &pfs);
				e += s - e - 1;
			}
			else
				s = e++ + 1;
		}
	}
	pfs.len += e - s;
	write(1, &fmt[s], e - s);
	va_end(ap);
	return (pfs.len);
}
