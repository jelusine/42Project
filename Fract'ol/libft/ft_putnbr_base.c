/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:22:39 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/09 17:32:45 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static	void	ft_putnbr_mod(int n, const char *base, int x)
{
	if (n == -2147483648)
	{
		ft_putnbr_mod(-21474, base, x);
		n = 83648;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= x)
		ft_putnbr_mod(n / x, base, x);
	ft_putchar(base[n % x]);
}

void			ft_putnbr_base(int nbr, const char *base)
{
	if (ft_analyse_base(base) == 1)
		ft_putnbr_mod(nbr, base, ft_strlen(base));
}
