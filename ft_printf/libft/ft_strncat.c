/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:32:34 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/12 22:22:17 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t		i;
	const int	x = ft_strlen(dest);

	i = -1;
	while (src[++i] && i < n)
		dest[x + i] = src[i];
	dest[x + i] = '\0';
	return (dest);
}
