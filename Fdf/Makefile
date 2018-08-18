# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelusine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 13:05:27 by jelusine          #+#    #+#              #
#    Updated: 2018/08/18 23:28:46 by jelusine         ###   ########.fr        #
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
	gcc $(FLAG) -o $(NAME) $(OBJ) -L minilibx_macos -lmlx -L libft -l ft $(FLAGS) -I minilibx_macos -g -fsanitize=address

%.o: %.c
	gcc $(FLAG) -c $<

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re fdf
