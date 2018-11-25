/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 15:14:29 by jelusine          #+#    #+#             */
/*   Updated: 2018/05/05 15:20:39 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lst_remove_if_size(t_list **begin, size_t dataref,
		void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *tmp2;

	tmp = *begin;
	while (tmp && dataref == tmp->content_size)
	{
		tmp = tmp->next;
		ft_lstdelone(begin, del);
		*begin = tmp;
	}
	while (tmp && tmp->next)
	{
		if (tmp->next->content_size == dataref)
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(&tmp2, del);
		}
		tmp = tmp->next;
	}
}
