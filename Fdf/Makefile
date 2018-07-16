# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelusine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 13:05:27 by jelusine          #+#    #+#              #
#    Updated: 2018/07/16 02:52:41 by jelusine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_parser.c\
		ft_parser2.c\
		playtest.c\
		main.c

OBJ = $(SRC:.c=.o)

NAME = fdf

FLAG = -Wall -Werror -Wextra

FLAGS = -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx_macos
	gcc $(FLAG) $(OBJ) -L minilibx_macos -lmlx -L libft -l ft $(FLAGS) -I minilibx_macos -g -fsanitize=address

%.o: %.c
	gcc $(FLAG) -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
