/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcolor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:06:40 by jelusine          #+#    #+#             */
/*   Updated: 2018/05/09 14:11:23 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	deja_vu(const char *str, int n)
{
	int i;

	i = -1;
	while (++i < n)
	{
		if (str[i] == str[n])
			return (0);
	}
	return (1);
}

void		ft_charcolor(const char c, const char *color)
{
	int				i;
	int				n;
	const char		*tab[10] = {"1", "2", "4", "31", "32",
								"33", "34", "35", "36", "37"};

	if (color)
	{
		n = -1;
		ft_putstr("\033[");
		while ((i = ft_charcmpstr(color[++n], "+-_")) != -1)
		{
			if (deja_vu(color, n) == 1)
			{
				ft_putstr(tab[i]);
				ft_putchar(';');
			}
		}
		if ((i = ft_charcmpstr(color[n], "rgybpcwRGYBPCW")) == -1)
			i = 6;
		ft_putstr(tab[i % 7 + 3]);
		ft_putchar('m');
		ft_putchar(c);
		ft_putstr("\033[0m");
	}
}
