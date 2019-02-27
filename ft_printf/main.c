/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 23:31:20 by jelusine          #+#    #+#             */
/*   Updated: 2019/01/23 06:07:25 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

//int main(void)
int		main(int ac, char **av)
{
	int x;

	//»·long long l;
	//»·if (ac == 4)
	//»·  ft_printf(av[1] , av[2], ft_atoi(av[3]));
	//»·if (ac == 3)
	//»·{
	//»·  l = -2147483648000000000;
	if (ac == 3)
	{
		printf("|%f|\n", 9.9 + ft_pow(ft_atoi(av[1]), ft_atoi(av[2])));
	}
	if (ac == 4)
	{
		if (av[3][0] == 'n')
		{
			ft_putnbr(ft_printf(av[1] , atoll(av[2])/*FTEST*/));NL;
			x = printf(av[1] , atoll(av[2])/*FTEST*/);
			printf("%d", x);
		}
		else
		{
			ft_putnbr(ft_printf(av[1] , av[2]));NL
			x = printf(av[1] , av[2]);
			printf("%d", x);
		}
	}
//	if (ac == 3)
//		ft_nb_len(ft_atoi(av[1]), ft_atoi(av[2]));
//	char t = 'd';
//	printf("1|%hho|\n2|%c|\n", t, t);
	//»·}
	//»·else if (ac == 2)
	//»·  ft_printf(av[1]);
/*	int i;
	if (ac == 2)
	{
		i = ft_atoi(av[1]);
		printf("|%hhd|\n|%#10o|\n", (char)i, i);
	}*/
	//»·unsigned int a = 0xFFFF;
	//»·unsigned int b = 0x0000;

	//»·if (a & b)
	//»·  TEST1
	return (0);
}
