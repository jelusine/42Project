/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:37:43 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/04 19:57:49 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*tsrc;
	char	*tdst;

	i = -1;
	tsrc = (char *)src;
	tdst = (char *)dst;
	while (++i < n)
		tdst[i] = tsrc[i];
	return (tdst);
}
