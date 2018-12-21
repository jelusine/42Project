/* ************************************************************************** */
/*                                                                            */
  3 /*                                                        :::      ::::::::   */
  4 /*   ft_printf.c                                        :+:      :+:    :+:   */
  5 /*                                                    +:+ +:+         +:+     */
  6 /*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
  7 /*                                                +#+#+#+#+#+   +#+           */
  8 /*   Created: 2018/12/06 05:04:17 by jelusine          #+#    #+#             */
  9 /*   Updated: 2018/12/21 02:16:32 by jelusine         ###   ########.fr       */
 10 /*                                                                            */
 11 /* ************************************************************************** */
 12
 13 #include "./ft_printf.h"
 14
 15 void»···fnc_char(t_pfs pfs)
 16 {
 17 »···char c;
 18
 19 »···c = va_arg(pfs.ap, int);
 20 »···ft_putchar(c);
 21 }
 22
 23
 24 void»···fnc_int(t_pfs pfs)
 25 {
 26 »···int d;
 27
 28 »···d = va_arg(pfs.ap, typeof(d));
 29 »···ft_putnbr(d);
 30 }
 31
 32 void»···ft_putinfnbr(long long int l)
 33 {
 34 »···if (l < 0)
 35 »···{
 36 »···»···ft_putchar('-');
 37 »···»···l *= -1;
 38 »···}
 39 »···if (l >= 100000000)
 40 »···»···ft_putinfnbr(l / 100000000);
 41 »···if (l && !(l % 100000000))
 42 »···»···ft_putstr("00000000");
 43 »···else
 44 »···»···ft_putnbr(l % 100000000);
 45 }
 46
 47 void»···fnc_long(t_pfs pfs)
 48 {
 49 »···long d;
  50
  51 »···d = va_arg(pfs.ap, long);
  52 »···ft_putinfnbr(d);
  53 }
  54
  55 void»···fnc_str(t_pfs pfs)
  56 {
  57 »···char *s;
  58
  59 »···s = va_arg(pfs.ap, typeof(s));
  60 »···ft_putstr(s);
  61 }
  62
  63 void»···fnc_oct(t_pfs pfs)
  64 {
  65 »···int o;
  66
  67 »···o = va_arg(pfs.ap, int);
  68 »···if (pfs.key & 0x0001)
  69 »···»···ft_putchar('0');
  70 »···ft_putnbr_base(o, "01234567");
  71 }
  72
  73 void»···fnc_hexa(t_pfs pfs, int i)
  74 {
  75 »···int»»···»···»···»···h;
  76 »···static const char»··*str[4] = {"0123456789ABCDEF", "0123456789abcdef",
  77 »···»···»···»···»···»···»···»···»···"0X", "0x"};
  78
  79 »···h = va_arg(pfs.ap, int);
  80 »···if (pfs.key & 0x0001)
  81 »···»···write(1, str[i + 2], 2);
  82 »···ft_putnbr_base(h, str[i]);
  83 }
  84
  85
  86 int»»···ft_parsing(char *str, t_pfs *pfs)
  87 {
  88 »···int»i;
  89 »···int»n;
  90 »···int j;
  91 //»·static t_fnctpf»»···tabfn[7] = {{fnc_char}, {fnc_int}, {fnc_str}, {fnc_oct}, {    fnc_hexa}, {fnc_int}, {fnc_long}};
  92
  93 »···i = -1;
  94 »···n = 0;
  95 »···while (str[++i])
  96 »···{
 97 »···»···if (str[i] == '#' && ++n)
 98 »···»···»···pfs->key = pfs->key | 0x0001;
 99 //»·»···else if ((j = ft_charcmpstr(str[i], "cdsoxil")) > -1 && ++n)
100 //»·»···»···tabfn[j].f(*pfs);
101 »···»···if (str[i] == 'c' && ++n)
102 »···»···»···fnc_char(*pfs);
103 »···»···else if (str[i] == 's' && ++n)
104 »···»···»···fnc_str(*pfs);
105 »···»···else if ((str[i] == 'd' || str[i] == 'i') && ++n)
106 »···»···»···fnc_int(*pfs);
107 »···»···else if (str[i] == 'o' && ++n)
108 »···»···»···fnc_oct(*pfs);
109 »···»···else if ((str[i] == 'x' || str[i] == 'X') && ++n)
110 »···»···»···fnc_hexa(*pfs, (str[i] - 88) / 32);
111 »···»···else if (str[i] == 'l' && (str[i] == 'd' || str[i] == 'i') && (n += 2))
112 »···»···»···fnc_long(*pfs);
113 »···}
114 »···return (n);
115 }
116
117 void ft_printf(char *fmt, ...)
118 {
119 »···t_pfs»··»···pfs;
120 »···va_list»»···ap;
121 »···int»»···»···s;
122 »···int»»···»···e;
123 »···int»»···»···i;
124
125
126 »···pfs.key = 0;
127 »···va_start(pfs.ap, fmt);
128 »···s = 0;
129 »···e = -1;
130 »···while (fmt[++e])
131 »···{
132 »···»···if (fmt[e] == '%')
133 //»·»···if (fmt[e] == '%')
134 »···»···{
135 »···»···»···write(1, &fmt[s], e - s);
136 »···»···»···s = e + ft_parsing(&fmt[e], &pfs) + 1;
137 »···»···»···e += s - e;
138 »···»···}
139 »···}
140 »···write(1, &fmt[s], e - s);
141 »···va_end(ap);
142 }
143
144 //int»··»···main(int ac, char **av)
145 int»»···main(void)
146 {
147 //»·long long l;
148
149 //»·if (ac == 4)
150 //»·»···ft_printf(av[1] , av[2], ft_atoi(av[3]));
151 //»·if (ac == 3)
152 //»·{
153 //»·»···l = -2147483648000000000;
154 »···»···ft_printf("test %x\n" , 42);
155 //
156 »···char t = 'd';
157 »···»···printf("1|%hho|\n2|%c|\n", t, t);
158 //»·}
159 //»·else if (ac == 2)
160 //»·»···ft_printf(av[1]);
161 /*»·int i;
162 »···if (ac == 2)
163 »···{
164 »···»···i = ft_atoi(av[1]);
165 »···»···printf("|%hhd|\n|%#10o|\n", (char)i, i);
166 »···}*/
167 //»·unsigned int a = 0xFFFF;
168 //»·unsigned int b = 0x0000;
169
170 //»·if (a & b)
171 //»·»···TEST1
172 »···return (0);
173 }
