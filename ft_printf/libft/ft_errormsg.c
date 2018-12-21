/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errormsg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 00:07:55 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/12 21:35:51 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft.h"

int		ft_errormsg(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (0);
}
