/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 05:04:17 by jelusine          #+#    #+#             */
/*   Updated: 2019/03/05 07:44:12 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

/*
** 	Pfs->key:
**	0x80: '#'
**	0x40: '0'
**	0x20: '+'
**	0x10: ' '
**
**	0x08: '-''
**	0x04: 'l'
**	0x02: 'h'
**	0x01:
*/

int		ft_anal_flag(char *str, t_pfs *pfs, int n)
{
	if (str[n] == '#')
		pfs->key = pfs->key | 0x80;
	else if (ft_isdigit(str[n]) && str[n - 1] != 46 && !ft_isdigit(str[n - 1]))
	{
		if (str[n] == '0' && !(pfs->key & 0x08))
			pfs->key = pfs->key | 0x40;
		pfs->pad = ft_max(ft_atoi(&str[n]), pfs->pad);
	}
	else if (str[n] == '+' && (pfs->key = pfs->key | 0x20))
		pfs->key = pfs->key & 0xef;
	else if (!(pfs->key & 0x20) && str[n] == ' ')
		pfs->key = pfs->key | 0x10;
	else if (str[n] == '-' && (pfs->key = pfs->key | 0x8))
		pfs->key = pfs->key & 0xbf;
	else if (!(pfs->key & 0x4) && str[n] == 'l' && (pfs->key = pfs->key | 0x4))
		pfs->key = pfs->key & (str[n + 1] == 'l' ? 0xfd : 0xfc);
	else if (!(pfs->key & 0x04) && str[n] == 'h')
		pfs->key = pfs->key | (str[n + 1] == 'h' ? 0x03 : 0x02);
	else if (str[n] == '.' && (pfs->prec = ft_atoi(&str[n + 1])))
		return (ft_nb_len(pfs->prec, 10) + 1);
	return (1);
}

void	ft_init(char *str, t_pfs *pfs, int i)
{
	if (ft_charcmpstr(str[i], "cspdiouxXfF") < 0)
	{
		pfs->str = ft_strdup("0");
		pfs->str[0] = str[i];
		pfs->strlen = (str[i] ? 1 : 0);
		pfs->prec = -1;
	}
	if (str[i] == 'c')
		fnc_char(pfs);
	else if (str[i] == 's')
		fnc_str(pfs);
	else if ((str[i] == 'u') && (pfs->type = pfs->type | 0x02))
		fnc_uint(pfs);
	else if ((str[i] == 'd' || str[i] == 'i') && (pfs->type = pfs->type | 0x01))
		fnc_int(pfs);
	else if (str[i] == 'o' && (pfs->type = pfs->type | 0x04))
		fnc_oct(pfs);
	else if (((str[i] == 'p' && (pfs->key = pfs->key | 0x80)) || str[i] == 'x'
			|| str[i] == 'X') && (pfs->type = pfs->type | 0x08))
		fnc_oct(pfs);
	else if (str[i] == 'f' && (pfs->type = pfs->type | 0x01))
		fnc_float(pfs);
	i = ft_max(pfs->prec, pfs->strlen - (*pfs->str == '-' ? pfs->type % 2 : 0));
	pfs->pad -= i - (!(pfs->prec || *pfs->str != '0') && pfs->pad > 0 ? 1 : 0);
	pfs->len += i + ft_max(pfs->pad, 0) - 1;
}

void	ft_affichage(t_pfs *pfs, int t, char i)
{
	if (pfs->type & 0x01 && pfs->key & 0x30 && pfs->str[0] != '-')
		ft_putchar(21 + (pfs->key & 0x30) * 11 / 16);
	if (pfs->key & 0x80 && (pfs->str[0] != '0' || i == 'p')
			&& pfs->type & 0x0c && (pfs->len += (pfs->type & 0x0c) / 4))
		write(1, (i == 'X' ? "0X" : "0x"), (pfs->type & 0x0c) / 4);
	if (pfs->prec > 0 || (pfs->key & 0x40 && pfs->pad > -1))
	{
		if (pfs->str[0] == '-' && ++t && pfs->strlen--)
			ft_putchar('-');
		pfs->prec -= pfs->strlen;
		if (pfs->prec < 0 && pfs->key & 0x40 && (pfs->prec = pfs->pad))
			pfs->pad = -1;
		ft_putnchar('0', pfs->prec);
	}
	if (i == 'X')
		ft_strtoupper(pfs->str);
	if ((pfs->prec || pfs->str[0] != '0'
			|| (pfs->key & 0x80 && pfs->type & 0x04)) && ++pfs->len)
	{
		write(1, &pfs->str[t], pfs->strlen);
		ft_strdel(&pfs->str);
	}
}

int		ft_parsing(char *str, t_pfs *pfs)
{
	int i;

	i = 1;
	while (str[i] && ft_charcmpstr(str[i], "#+- .0123456789lhL") > -1)
		i += ft_anal_flag(str, pfs, i);
	ft_init(str, pfs, i);
	if (pfs->pad > -1 && !(pfs->key & 0x08)
		&& (!(pfs->key & 0x40) || (pfs->prec >= 0
				&& pfs->key & 0x40 && pfs->type & 0x0f)))
		pfs->pad = ft_putnchar(' ', pfs->pad);
	ft_affichage(pfs, 0, str[i]);
	pfs->pad = ft_putnchar(' ', pfs->pad);
	return ((str[i] ? i + 1 : i));
}

int		ft_printf(char *fmt, ...)
{
	t_pfs	pfs;
	va_list	ap;
	int		se[2];

	ft_bzero(&pfs, sizeof(t_pfs));
	va_start(pfs.ap, fmt);
	se[0] = pfs.prec--;
	se[1] = --pfs.pad;
	while (fmt[++se[1]])
	{
		if (fmt[se[1]] == '%' || fmt[se[1]] == '{')
		{
			write(1, &fmt[se[0]], se[1] - se[0]);
			pfs.len += se[1] - se[0];
			if (fmt[se[1]] == '{')
				se[0] = se[1] + ft_pfcolor(&fmt[se[1] + 1], &pfs.len, &pfs.col);
			else
				se[0] = se[1] + ft_parsing(&fmt[se[1]], &pfs);
			se[1] += se[0] - se[1] - 1;
		}
	}
	write(1, &fmt[se[0]], se[1] - se[0]);
	va_end(ap);
	ft_putstr((pfs.col ? "\033[0m" : ""));
	return (pfs.len + se[1] - se[0]);
}
