/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:48:34 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/09 14:50:24 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstadd(t_list **alst, t_list *newele)
{
	if (newele)
		newele->next = *alst;
	*alst = newele;
}
