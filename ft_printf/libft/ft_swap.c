/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 03:11:50 by jelusine          #+#    #+#             */
/*   Updated: 2018/08/21 03:12:42 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return (1);
}
