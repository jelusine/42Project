/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:57:53 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/07 13:19:44 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(char const *str, char const *to_find, size_t len)
{
	int s;
	int c;
	int a;

	if (!(to_find[0]))
		return ((char *)str);
	c = -1;
	while (str[++c])
	{
		a = 0;
		if (str[c] == to_find[a--])
		{
			s = c;
			while (str[c] == to_find[++a] && str[c] && (size_t)c < len)
				c++;
			if (!to_find[a])
				return ((char *)&str[s]);
			c = s + 1;
		}
	}
	return (0);
}
