/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 05:04:17 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/09 07:42:04 by jelusine         ###   ########.fr       */
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
	while (str[i] && ft_charcmpstr(str[i], "cspdiouuxXf") < 0)
		i++;
	n = 0;
	while (++n < i)
	{
		if (str[n] == '#')
			pfs->key = pfs->key | 0x80;
		else if (ft_isdigit(str[n]) && str[n - 1] != '.' && !ft_isdigit(str[n - 1]))
		{
			if (str[n] == '0' && pfs->prec < 0 && !(pfs->key & 0x08))
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
		{
			pfs->prec = ft_atoi(&str[n + 1]);
			pfs->key = pfs->key & 0xbf;
		}
	}
	if (str[i] == 'c')
		fnc_char(pfs);
	else if (str[i] == 's')
		fnc_str(pfs);
	else if ((str[i] == 'd' || str[i] == 'i') && (pfs->type = pfs->type | 0x01))
	{
		if ((pfs->key & 0x05) == 4)
			fnc_long(pfs);
		else
			fnc_int(pfs);
	}
	else if (str[i] == 'u' && (pfs->type = pfs->type | 0x02))
		fnc_uint(pfs);
	else if (str[i] == 'o' && (pfs->type = pfs->type | 0x04))
		fnc_oct(pfs);
	else if ((str[i] == 'x' || str[i] == 'X') && (pfs->type = pfs->type | 0x08))
		fnc_hexa(pfs, (str[i] - 88) / 32);
	else
		return (i);
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
	while (fmt[++e])
	{
		if (fmt[e] == '%')
		{
			write(1, &fmt[s], e - s);
			if (fmt[e + 1] != '%')
			{
				pfs.len += e - s;
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
