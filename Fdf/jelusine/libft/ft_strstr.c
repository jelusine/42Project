/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:23:22 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/07 12:33:17 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strstr(char const *str, char const *to_find)
{
	int c;

	if (!(to_find[0]))
		return ((char *)str);
	c = -1;
	while (str[++c])
	{
		if (str[c] == to_find[0])
		{
			if (ft_strncmp(&str[c], to_find, ft_strlen(to_find)) == 0)
				return ((char *)&str[c]);
		}
	}
	return (NULL);
}
