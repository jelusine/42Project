/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:25:17 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/07 15:05:25 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int i;

	i = ft_strlen(str) + 1;
	while (--i > -1)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
	}
	return (NULL);
}
