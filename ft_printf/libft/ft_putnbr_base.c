/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:22:39 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/09 01:37:49 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static	void	ft_putnbr_mod(unsigned int n, const char *base, unsigned int x)
{
	if (n >= x)
		ft_putnbr_mod(n / x, base, x);
	ft_putchar(base[n % x]);
}

void			ft_putnbr_base(int nbr, const char *base)
{
	if (ft_analyse_base(base) == 1)
		ft_putnbr_mod(nbr, base, ft_strlen(base));
}
