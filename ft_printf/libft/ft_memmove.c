/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:23:42 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/09 15:27:52 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*tsrc;
	char	*tdst;

	i = -1;
	tsrc = (char *)src;
	tdst = (char *)dst;
	while (++i < n)
		tdst[(src > dst ? i : n - 1 - i)] = tsrc[(src > dst ? i : n - 1 - i)];
	dst = tdst;
	return (dst);
}
