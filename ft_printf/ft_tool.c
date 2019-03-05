/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 06:51:29 by jelusine          #+#    #+#             */
/*   Updated: 2019/03/05 08:00:39 by jelusine         ###   ########.fr       */
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

int		ft_putnchar(char c, int n)
{
	while (n-- > 0)
		ft_putchar(c);
	return (0);
}

int		ft_strtoupper(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
	return (0);
}

char	*ft_utoa_base(unsigned long nb, unsigned int tbse)
{
	char			*str;
	unsigned long	i;
	int				n;
	const char		*base = "0123456789ABCDEF";

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
