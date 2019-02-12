/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:43:08 by jelusine          #+#    #+#             */
/*   Updated: 2019/02/12 18:44:49 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

/*
**  SETCOL: 0)red 1)green 2)yellow 3)blue 4)purple 5)cyan 6)white 7)eoc
*/

int		ft_pfcolor(const char *str, int *pflen)
{
	char		i;
	int			len;
	const char	*set;

	i = -1;
	set = SETCOL;
	while (++i < 8 && ft_strncmp(str, set, (len = ft_strlen(set))))
		set += len + 1;
	if ((i >= 8
		|| (!(i < 7 && ft_charcmpstr(str[len], "+-_") > -1 && str[len + 1] == '}')
			&& str[len] != '}')) && ++*pflen)
		return (1 + ft_errormsg("{"));
	ft_putstr("\033[");
	ft_putnbr((31 + i) % 38);
	while ((i = ft_charcmpstr(str[len++], "+-_")) != -1)
	{
		ft_putchar(';');
		ft_putnbr((i == 2 ? 3 : i) + 1);
	}
	ft_putchar('m');
	return (len + 1);
}
