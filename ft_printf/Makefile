# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelusine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 18:18:46 by jelusine          #+#    #+#              #
#    Updated: 2019/01/06 01:26:29 by jelusine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCC =	ft_printf.c\
		ft_fncpf.c\
		ft_pfcolor.c\
		ft_tool.c\
		ft_float.c

LAG = -Wall -Werror -Wextra

SRCO = $(SRCC:.c=.o)

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(SRCO)
	make -C libft
	ar rcs $@ $(SRCO) libft/*.o

printf: all
	gcc $(LAG) -c main.c
	gcc $(LAG) main.o $(NAME) -o printf

%.o: %.c
	gcc $(LAG) -c $<

clean:
	make -C libft clean
	rm -rf $(SRCO)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
