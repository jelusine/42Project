/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:58:32 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/12 22:19:16 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memalloc(size_t len)
{
	int		*huh;

	if (!(huh = (int *)malloc(sizeof(int) * len)))
		return (NULL);
	ft_bzero(huh, len);
	return (huh);
}
