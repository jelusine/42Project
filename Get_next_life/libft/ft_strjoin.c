/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:19:28 by jelusine          #+#    #+#             */
/*   Updated: 2018/06/02 21:51:02 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	if (!(s1 && s2) || !(str = (char *)malloc(sizeof(char) *
					((i = ft_strlen(s1)) + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcpy(str + i, s2);
	return (str);
}
