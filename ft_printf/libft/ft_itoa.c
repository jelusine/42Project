/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:25:50 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/12 22:18:31 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_itoa(int nb)
{
	char	*str;
	long	i;
	int		n;

	n = (nb < 0 ? 2 : 1);
	i = ft_abs(nb);
	while (i > 9)
	{
		n++;
		i /= 10;
	}
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	str[n--] = '\0';
	str[0] = (nb < 0 ? '-' : '0');
	i = ft_abs(nb);
	while (i > 0)
	{
		str[n--] = i % 10 + 48;
		i /= 10;
	}
	return (str);
}
