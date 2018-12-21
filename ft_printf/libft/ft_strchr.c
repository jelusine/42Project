/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:20:58 by jelusine          #+#    #+#             */
/*   Updated: 2018/06/04 18:47:15 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *str, int c)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
	}
	if (str[i] == c)
		return ((char *)&str[i]);
	return (NULL);
}
