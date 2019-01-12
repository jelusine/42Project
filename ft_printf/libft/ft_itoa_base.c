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

char	*ft_itoa_base(long nb, int tbse)
{
	char		*str;
	long		i;
	int			n;
	const char	*base = "0123456789ABCDEF";

	if (tbse < 1 || 16 < tbse)
		return (0);
	n = (nb < 0 && tbse == 10 ? 2 : 1);
	i = (nb < 0 && tbse == 10 ? -nb : (unsigned long)nb);
	tbse += (tbse == 1 ? 26 : 0);
	while ((i >= (tbse % 17) || -(tbse % 17) >= i) && ++n)
		i /= (tbse % 17);
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	str[n--] = '\0';
	str[0] = (nb < 0 ? '-' : '0');
	i = (nb < 0 && tbse == 10 ? -nb : (unsigned long)nb) * (tbse % 17);
	while ((i /= (tbse % 17)) > 0)
		str[n--] = base[i % (tbse % 17)];
	return (str);
}
