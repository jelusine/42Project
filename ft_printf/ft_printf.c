/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 05:04:17 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/06 06:18:56 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		ft_nb_len(int nb, int base)
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
//	ft_putnbr(i); TEST1
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
//		ft_putnbr(pfs->key); TEST5
	}
	if (str[i] == 'c')
		fnc_char(pfs);
	else if (str[i] == 's')
		fnc_str(pfs);
	else if ((str[i] == 'd' || str[i] == 'i'))
		fnc_int(pfs);
	else if (str[i] == 'o')
		fnc_oct(pfs);
	else if (str[i] == 'x' || str[i] == 'X')
		fnc_hexa(pfs, (str[i] - 88) / 32);
/*	ft_putnbr(nk);NL
	ft_putnbr(i);NL
	ft_putnbr(pfs->key);NL*/
	return (i + 1);
}
/*{
	int	i;
	int	n;
	int j;
	//»·static t_fnctpf»  tabfn[7] = {{fnc_char}, {fnc_int}, {fnc_str}, {fnc_oct}, {    fnc_hexa}, {fnc_int}, {fnc_long}};

	i = 0;
	n = 0;
	while (str[++i])
	{
		if (str[i] == '#' && ++n && i++)
			pfs->key = pfs->key | 0x0001;
		//»·  else if ((j = ft_charcmpstr(str[i], "cdsoxil")) > -1 && ++n)
		//»·    tabfn[j].f(*pfs);
		if (str[i] == 'c' && ++n)
			fnc_char(*pfs);
		else if (str[i] == 's' && ++n)
			fnc_str(*pfs);
		else if (((str[i] == 'd' || str[i] == 'i') && ++n)
				|| (str[i] == 'h' && (str[i + 1] == 'd' || str[i + 1] == 'i')
					&& (n += 2) && ++i))
			fnc_int(*pfs);
		else if ((str[i] == 'x' && ++n)
				|| (str[i] == 'h' && (str[i + 1] == 'x') && (n += 2) && ++i))
			fnc_unsbas(*pfs, 1);
		else if ((str[i] == 'X' && ++n)
				|| (str[i] == 'h' && (str[i + 1] == 'X') && (n += 2) && ++i))
			fnc_unsbas(*pfs, 0);
		else if (str[i] == 'o' && ++n)
			fnc_oct(*pfs);
		else if ((str[i] == 'x' || str[i] == 'X') && ++n)
			fnc_hexa(*pfs, (str[i] - 88) / 32);
		else if (str[i] == 'l' && (str[i + 1] == 'd' || str[i + 1] == 'i') && (n += 2) && ++i)
			fnc_long(*pfs);
		else if (str[i] == 'l' && str[i + 1] == 'x' && (n += 2) && ++i)
			fnc_lhexa(*pfs);
		else
			break;
	}
	if (n)
		n++;
	return (n);
}*/

int		 ft_printf(char *fmt, ...)
{
	t_pfs	pfs;
	va_list	ap;
	int		s;
	int		e;

	pfs.key = 0;
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
