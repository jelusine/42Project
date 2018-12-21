/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:18:51 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/04 11:54:47 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft.h"

void	ft_putstr_fd(char const *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}
