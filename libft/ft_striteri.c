/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:47:18 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/07 18:42:12 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	int i;

	if (str && f)
	{
		i = -1;
		while (str[++i])
			f((unsigned int)i, &str[i]);
	}
}
