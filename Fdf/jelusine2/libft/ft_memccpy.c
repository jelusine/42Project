/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:45:08 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/05 14:49:28 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*tdst;
	char	*tsrc;

	i = -1;
	tsrc = (char *)src;
	tdst = (char *)dst;
	while (++i < n)
	{
		tdst[i] = tsrc[i];
		if ((unsigned char)tsrc[i] == (unsigned char)c)
			return (&dst[i + 1]);
	}
	return (NULL);
}
