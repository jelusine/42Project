/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_rename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 05:20:28 by jelusine          #+#    #+#             */
/*   Updated: 2018/10/03 07:20:36 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Fract'ol.h"

int		ft_tracking(int x, int y, void *ptr)
{
	t_test *test = ptr;
	const int		s = test->sel_fra - 1;
	const double	tmpx = x / test->zoom + test->limx[s][0];
	const double	tmpy = y / test->zoom + test->limy[s][0];
//	const float		ecx = (fabs(test->limx[s][0]) + fabs(test->limx[s][1])) / 2;
//	const float		ecy = (fabs(test->limy[s][0]) + fabs(test->limy[s][1])) / 2;

	if (test->lock > 0)
	{
		test->jc.r = tmpx;
		test->jc.i = tmpy;
		ft_mouse(0, 0, 0, test);
	}
	return (0);
}
