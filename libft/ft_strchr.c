/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:20:58 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/16 14:09:00 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strchr(const char *str, int c)
{
	int			i;
	const int	x = ft_strlen(str);

	i = -1;
	while (++i <= x)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
	}
	return (NULL);
}
