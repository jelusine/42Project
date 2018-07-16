/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:57:17 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/05 17:59:47 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*st1;
	char	*st2;

	if (n == 0)
		return (0);
	i = 0;
	st1 = (char *)s1;
	st2 = (char *)s2;
	while (i < n - 1 && (st1[i] == st2[i]))
		i++;
	return ((unsigned char)st1[i] - (unsigned char)st2[i]);
}
