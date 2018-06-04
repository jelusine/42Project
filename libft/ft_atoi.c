/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:35:40 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/16 13:43:28 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int		ft_atoi(char const *str)
{
	int nb;
	int neg;
	int i;

	i = 0;
	neg = 1;
	nb = 0;
	while (ft_charcmpstr(str[i], " \n\t\r\v\f") != -1)
		i++;
	if (ft_charcmpstr(str[i], "-+") != -1)
	{
		if (str[i++] == '-')
			neg = -1;
	}
	while ('0' <= str[i] && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	return (neg * nb);
}
