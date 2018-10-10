# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelusine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 13:05:27 by jelusine          #+#    #+#              #
#    Updated: 2018/09/11 05:33:59 by jelusine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c\
		playtest.c\
		a_rename.c

OBJ = $(SRC:.c=.o)

NAME = fractol

FLAG = -Wall -Werror -Wextra

FLAGS = -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx_macos
	gcc $(FLAG) -o $(NAME) $(OBJ) -L minilibx_macos -lmlx -L libft -lft $(FLAGS) -I minilibx_macos

%.o: %.c
	gcc $(FLAG) -c $<

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
