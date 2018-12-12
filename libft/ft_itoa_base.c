/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:33:43 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/12 22:18:39 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_itoa_base(int nb, int tbse)
{
	char		*str;
	long		i;
	int			n;
	const char	*base = "0123456789ABCDEF";

	if (tbse < 2 || 16 < tbse)
		return (0);
	n = (nb < 0 && tbse == 10 ? 2 : 1);
	i = ft_abs(nb);
	while (i >= tbse)
	{
		n++;
		i /= tbse;
	}
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	str[n--] = '\0';
	str[0] = (nb < 0 ? '-' : '0');
	i = ft_abs(nb);
	while (i > 0)
	{
		str[n--] = base[i % tbse];
		i /= tbse;
	}
	return (str);
}
