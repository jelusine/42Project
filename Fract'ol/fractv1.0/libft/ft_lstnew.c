/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:17:14 by jelusine          #+#    #+#             */
/*   Updated: 2018/05/28 13:10:33 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list		*ft_lstnew(void const *content, size_t len)
{
	t_list	*tmp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		tmp->content = 0;
		tmp->content_size = 0;
	}
	else
	{
		if (!(tmp->content = (void *)malloc(len)))
			return (NULL);
		ft_memcpy(tmp->content, content, len);
		tmp->content_size = len;
	}
	tmp->next = NULL;
	return (tmp);
}
