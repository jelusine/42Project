/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:38:43 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/07 15:39:07 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *tmp2;

	tmp = *alst;
	if (tmp)
	{
		tmp2 = tmp->next;
		while (tmp && tmp2)
		{
			ft_lstdelone(&tmp, del);
			tmp = tmp2;
			tmp2 = tmp2->next;
		}
		ft_lstdelone(&tmp, del);
	}
	*alst = NULL;
}
