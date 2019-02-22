/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:33:43 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/12 14:46:13 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>

char	*ft_itoa_base(long long int nb, int tbse)
{
	char						*str;
	long long	int 	i;
	int							n;
	const char			*base = "0123456789abcdef";

	if (tbse < 1 || 16 < tbse)
		return (0);
	n = (nb < 0 && tbse == 10 ? 2 : 1);
	i = (nb < 0 && tbse == 10 ? -nb : (unsigned long long)nb);
	if (nb == (long long int)0x8000000000000000)
		i = 8223372036854775808;
	tbse += (tbse == 1 ? 26 : 0);
	while ((i >= (tbse % 17)) && ++n)
		i /= (tbse % 17);
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	str[n--] = '\0';
	str[0] = (nb < 0 ? '-' : '0');
	i = (nb < 0 && tbse == 10 ? nb : (unsigned long long)nb);
	while (i > 0 || 0 > i)
	{
		str[n--] = base[ft_abs(i % (tbse % 17))];
		i /= (tbse % 17);
	}
	return (str);
}
