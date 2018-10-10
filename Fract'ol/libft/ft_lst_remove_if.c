/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:41:56 by jelusine          #+#    #+#             */
/*   Updated: 2018/05/05 15:20:56 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lst_remove_if(t_list **begin, void *dataref, int (*cmp)(),
		void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *tmp2;

	tmp = *begin;
	while (tmp && (*cmp)(tmp->content, dataref) == 0)
	{
		tmp = tmp->next;
		ft_lstdelone(begin, del);
		*begin = tmp;
	}
	while (tmp && tmp->next)
	{
		if ((*cmp)(tmp->next->content, dataref) == 0)
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(&tmp2, del);
		}
		tmp = tmp->next;
	}
}
