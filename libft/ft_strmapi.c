/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:56:30 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/12 22:22:13 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strmapi(char const *src, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!(src) || !f ||
			!(str = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	i = -1;
	while (src[++i])
		str[i] = f((unsigned int)i, src[i]);
	str[i] = '\0';
	return (str);
}
