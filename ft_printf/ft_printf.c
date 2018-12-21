/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 05:04:17 by jelusine          #+#    #+#             */
/*   Updated: 2018/12/21 05:22:49 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

void  fnc_char(t_pfs pfs)
{
	char c;

	c = va_arg(pfs.ap, int);
	ft_putchar(c);
}

void  fnc_int(t_pfs pfs)
{
	int d;

	d = va_arg(pfs.ap, typeof(d));
	ft_putnbr(d);
}

void  ft_putinfnbr(long long int l)
{
	if (l < 0)
	{
		ft_putchar('-');
		l *= -1;
	}
	if (l >= 100000000)
		ft_putinfnbr(l / 100000000);
	if (l && !(l % 100000000))
		ft_putstr("00000000");
	else
		ft_putnbr(l % 100000000);
}

void  fnc_long(t_pfs pfs)
{
	long d;

	d = va_arg(pfs.ap, long);
	ft_putinfnbr(d);
}

void  fnc_str(t_pfs pfs)
{
	char *s;

	s = va_arg(pfs.ap, typeof(s));
	ft_putstr(s);
}

void  fnc_oct(t_pfs pfs)
{
	int o;

	o = va_arg(pfs.ap, int);
	if (pfs.key & 0x0001)
		ft_putchar('0');
	ft_putnbr_base(o, "01234567");
}

void  fnc_hexa(t_pfs pfs, int i)
{
	int        h;
	static const char	*str[4] = {"0123456789ABCDEF", "0123456789abcdef",
		"0X", "0x"};

	h = va_arg(pfs.ap, int);
	if (pfs.key & 0x0001)
		write(1, str[i + 2], 2);
	ft_putnbr_base(h, str[i]);
}

void	fnc_unsbas(t_pfs pfs, int i)
{
	unsigned int u;
	static const char	*str[4] = {"0123456789ABCDEF", "0123456789abcdef",
		"0X", "0x"};

	u = va_arg(pfs.ap, typeof(u));
	if (pfs.key & 0x0001)
		write(1, str[i + 2], 2);
	ft_putnbr_base(u, str[i]);
}

int  ft_parsing(char *str, t_pfs *pfs)
{
	int	i;
	int	n;
	int j;
	//»·static t_fnctpf»  tabfn[7] = {{fnc_char}, {fnc_int}, {fnc_str}, {fnc_oct}, {    fnc_hexa}, {fnc_int}, {fnc_long}};

	i = 0;
	n = 0;
	while (str[++i])
	{
		if (str[i] == '#' && ++n)
			pfs->key = pfs->key | 0x0001;
		//»·  else if ((j = ft_charcmpstr(str[i], "cdsoxil")) > -1 && ++n)
		//»·    tabfn[j].f(*pfs);
		if (str[i] == 'c' && ++n)
			fnc_char(*pfs);
		else if (str[i] == 's' && ++n)
			fnc_str(*pfs);
		else if (((str[i] == 'd' || str[i] == 'i') && ++n)
				|| (str[i] == 'h' && (str[i + 1] == 'd' || str[i + 1] == 'i')
					&& (n += 2) && ++i))
			fnc_int(*pfs);
		else if (((str[i] == 'o' || str[i] == 'x' || str[i] == 'X') && ++n)
				|| (str[i] == 'h' && (str[i + 1] == 'o' || str[i + 1] == 'x'
						|| str[i + 1] == 'X') && (n += 2) && ++i))
			fnc_int(*pfs);
		else if (str[i] == 'o' && ++n)
			fnc_oct(*pfs);
		else if ((str[i] == 'x' || str[i] == 'X') && ++n)
			fnc_hexa(*pfs, (str[i] - 88) / 32);
		else if (str[i] == 'l' && (str[i] == 'd' || str[i] == 'i') && (n += 2))
			fnc_long(*pfs);
		else
			break;
	}
	if (n)
		n++;
	return (n);
}

void ft_printf(char *fmt, ...)
{
	t_pfs	pfs;
	va_list	ap;
	int		s;
	int		e;
	int		i;

	pfs.key = 0;
	va_start(pfs.ap, fmt);
	s = 0;
	e = -1;
	while (fmt[++e])
	{
		if (fmt[e] == '%')
			//»·  if (fmt[e] == '%')
		{
			write(1, &fmt[s], e - s);
			s = e + ft_parsing(&fmt[e], &pfs);
			e += s - e;
		}
	}
	write(1, &fmt[s], e - s);
	va_end(ap);
}

//int»··  main(int ac, char **av)
int main(void)
{
	//»·long long l;

	//»·if (ac == 4)
	//»·  ft_printf(av[1] , av[2], ft_atoi(av[3]));
	//»·if (ac == 3)
	//»·{
	//»·  l = -2147483648000000000;
	ft_printf("test %hhi\n" , 42);
	//
//	char t = 'd';
//	printf("1|%hho|\n2|%c|\n", t, t);
	//»·}
	//»·else if (ac == 2)
	//»·  ft_printf(av[1]);
	/*»·int i;
	  162   if (ac == 2)
	  163   {
	  164     i = ft_atoi(av[1]);
	  165     printf("|%hhd|\n|%#10o|\n", (char)i, i);
	  166   }*/
	//»·unsigned int a = 0xFFFF;
	//»·unsigned int b = 0x0000;

	//»·if (a & b)
	//»·  TEST1
	return (0);
}
