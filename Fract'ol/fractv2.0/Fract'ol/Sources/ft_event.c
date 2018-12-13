/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 08:25:25 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/03 09:06:55 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fractol.h"

int		ft_tracking(int x, int y, void *ptr)
{
	t_test	*test;

	test = ptr;
	if (test->lock > 0 && S == 1)
	{
		test->jc.r = x / TFP[S].zoom + TFP[S].limxy[0];
		test->jc.i = y / TFP[S].zoom + TFP[S].limxy[1];
		fractest(test, 1, S);
	}
	return (0);
}

/*
**	Ft_key:
**
**	1) Esc
**	2) Fleche Gauche, Droite: Augmentation iteration max
**	3) WASD: Deplacement sur la Fractale
**	4) Return, Entree : Reinitialisation de la Fractale
**	5) T, Y; Augmentation de la puissance de "Multibrot"
**	6) Espace: Activation de la cle pour "Julia"
**	7) Fleche Haut, Bas: Changement de la Fractale
*/

int		ft_key(int key, void *ptr)
{
	t_test	*test;
	int		i;

	test = ptr;
	i = 0;
	if (key == 53)
		exit(1);
	if ((key == 123 && TFP[S].ite_max > 1)
			|| (key == 124 && TFP[S].ite_max < 1000))
		TFP[S].ite_max += 5 * (2 * key - 247) + i++;
	else if (key == 0 || key == 2 || key == 13 || key == 1)
		TFP[S].limxy[key % 2] += (40 / TFP[S].zoom)
			* ((key - 1) * (1 - key % 2) + (key % 2) * (7 - key) / 6) + i++;
	else if ((key == 36 || key == 76) && (test->lock = -1) && ++i)
		set_val(test, S, 1);
	else if (((key == 16 && TFP[S].n < 15) || (key == 17 && TFP[S].n > 2)))
		TFP[S].n += 33 - 2 * key + i++;
	else if (key == 49)
		test->lock *= -1;
	else if ((key == 125 || key == 126) && (test->lock = -1))
		test->s = (S + 1) % 2;
	return (fractest(test, i, S));
}

int		ft_mouse(int key, int x, int y, void *ptr)
{
	t_test *test;

	test = ptr;
	if (key == 4 || key == 5)
	{
		TFP[S].zoom *= (1.25 * (1 - key % 2)) + (0.8 * (key % 2));
		TFP[S].limxy[0] += (x - (WIDTH * 0.5)) / TFP[S].zoom;
		TFP[S].limxy[1] += (y - (HEIGHT * 0.5)) / TFP[S].zoom;
		return (fractest(test, 1, S));
	}
	else if (key == 3)
	{
		set_val(test, S, 0);
		return (fractest(test, 1, S));
	}
	return (0);
}
