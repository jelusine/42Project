/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fncpf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 02:10:00 by jelusine          #+#    #+#             */
/*   Updated: 2019/03/05 07:59:07 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
