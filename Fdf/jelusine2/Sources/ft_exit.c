/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 01:53:11 by jelusine          #+#    #+#             */
/*   Updated: 2018/11/16 23:50:02 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

int		ft_exit(int key, void *ptr)
{
	(void)key;
	(void)ptr;
	exit(0);
	return (0);
}