/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 21:01:35 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/07 18:13:57 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int		ft_charcmpstr(char c, const char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			return (i);
	}
	return (-1);
}