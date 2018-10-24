/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:30:27 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/09 17:30:58 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int		ft_analyse_base(const char *str)
{
	int c;
	int a;

	if (ft_strlen(str) < 2)
		return (0);
	c = -1;
	while (str[++c])
	{
		if (str[c] == '-' || str[c] == '+')
			return (0);
		a = c;
		while (str[++a])
		{
			if (str[c] == str[a])
				return (0);
		}
	}
	return (1);
}
