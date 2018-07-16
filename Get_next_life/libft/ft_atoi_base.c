/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 21:01:35 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/16 13:45:03 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static	int	ft_atoi_mod(const char *str, const char *base)
{
	int			nbr;
	int			i;
	int			neg;
	const	int	lgbs = ft_strlen(base);

	i = 0;
	neg = 1;
	nbr = 0;
	while (ft_charcmpstr(str[i], " \n\t\r\v\f") != -1)
		i++;
	if (ft_charcmpstr(str[i], "-+") != -1)
	{
		if (str[i++] == '-')
			neg = -1;
	}
	while (ft_charcmpstr(str[i], base) != -1)
		nbr = nbr * lgbs + ft_charcmpstr(str[i++], base);
	return (neg * nbr);
}

int			ft_atoi_base(const char *str, const char *base)
{
	int i;

	if (ft_analyse_base(base) == 0)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (ft_charcmpstr(str[i], base) < 0 && ft_charcmpstr(str[i], "+-") < 0)
			return (0);
	}
	return (ft_atoi_mod(str, base));
}
