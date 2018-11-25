/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:46:52 by jelusine          #+#    #+#             */
/*   Updated: 2018/05/28 13:11:22 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *))
{
	t_list *begin;
	t_list *tmpp;
	t_list *tmp;

	tmpp = lst;
	begin = NULL;
	if (tmpp && f)
	{
		if (!(begin = f(tmpp)))
			return (NULL);
		while (tmpp->next)
		{
			tmpp = tmpp->next;
			if (!(tmp = f(tmpp)))
				return (NULL);
			ft_lstaddend(&begin, tmp);
		}
	}
	return (begin);
}
