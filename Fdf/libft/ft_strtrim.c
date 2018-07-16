/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:35:58 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/04 15:31:07 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strtrim(char const *src)
{
	int		i;
	int		x;

	if (!(src))
		return (NULL);
	i = 0;
	while (src[i] && ft_charcmpstr(src[i], " \n\t") != -1)
		i++;
	if (!(src[i]))
		return (ft_strdup(""));
	x = ft_strlen(src) - 1;
	while (x > -1 && ft_charcmpstr(src[x], " \n\t") != -1)
		x--;
	return (ft_strsub(src, (unsigned int)i, (size_t)(x - i + 1)));
}
