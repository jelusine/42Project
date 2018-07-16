/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelusine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:49:59 by jelusine          #+#    #+#             */
/*   Updated: 2018/04/18 18:23:01 by jelusine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static	int		ft_fill(char **dest, char const *str, int y, char *kwords)
{
	int a;
	int c;
	int i;

	i = 0;
	while (str[i])
	{
		while (ft_charcmpstr(str[i], kwords) != -1)
			i++;
		a = i;
		while ((ft_charcmpstr(str[i], kwords) == -1) && str[i])
		{
			i++;
			if ((ft_charcmpstr(str[i], kwords) != -1) || !str[i])
			{
				if (!(dest[y] = (char *)malloc(sizeof(char) * (i - a + 1))))
					return (0);
				c = 0;
				while (a < i)
					dest[y][c++] = str[a++];
				dest[y++][c] = '\0';
			}
		}
	}
	return (0);
}

char			**ft_split(char const *str, char *kwords)
{
	char	**dest;
	int		i;
	int		nbes;

	if (!(str))
		return (NULL);
	i = 0;
	nbes = 0;
	while (str[i])
	{
		while (ft_charcmpstr(str[i], kwords) != -1)
			i++;
		while ((ft_charcmpstr(str[i], kwords) == -1) && str[i])
		{
			i++;
			if ((ft_charcmpstr(str[i], kwords) != -1) || !str[i])
				nbes++;
		}
	}
	if (!(dest = (char **)malloc(sizeof(*dest) * (nbes + 1))))
		return (NULL);
	dest[nbes] = 0;
	ft_fill(dest, str, 0, kwords);
	return (dest);
}
