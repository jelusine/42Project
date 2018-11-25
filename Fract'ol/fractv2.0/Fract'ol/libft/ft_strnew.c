/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:49:38 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/04 16:51:32 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnew(size_t len)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memset(str, '\0', len + 1);
	return (str);
}
