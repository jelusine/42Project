/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:24:45 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/16 14:32:48 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n && src[i])
		dest[i] = src[i];
	ft_memset(&dest[i], '\0', n - i);
	return (dest);
}
