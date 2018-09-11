# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelusine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 13:05:27 by jelusine          #+#    #+#              #
#    Updated: 2018/09/11 02:25:01 by jelusine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_parser2.c\
		ft_parser.c\
		playtest.c\
		ft_exit.c\
		ft_draw.c\
		main.c

OBJ = $(SRC:.c=.o)

NAME = fdf

FLAG = -Wall -Werror -Wextra

FLAGS = -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx_macos
	gcc $(FLAG) -o ./$(NAME) $(OBJ) -L minilibx_macos -lmlx -L libft -l ft $(FLAGS) -I minilibx_macos

%.o: %.c
	gcc $(FLAG) -c $<

clean:
	make clean -C libft
	make clean -C minilibx_macos
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
