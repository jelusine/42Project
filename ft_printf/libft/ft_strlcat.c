/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:56:32 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/12 22:21:59 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int i;
	unsigned int c;

	if ((unsigned int)ft_strlen(dest) > size)
		return (ft_strlen(src) + size);
	i = ft_strlen(dest);
	c = -1;
	while (src[++c] && i + c < size - 1)
		dest[i + c] = src[c];
	dest[i + c] = '\0';
	return (i + ft_strlen(src));
}
