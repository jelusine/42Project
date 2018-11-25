# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelusine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 13:05:27 by jelusine          #+#    #+#              #
#    Updated: 2018/11/25 08:15:30 by jelusine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c\
		efrac_calc.c

SRC_DIR = ./Sources/

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

NAME = fractol

FLAG = -Wall -Werror -Wextra

FLAGS = -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx_macos
	@gcc $(FLAG) -o $(NAME) -I Includes $(OBJ) -L minilibx_macos -lmlx -L libft -lft $(FLAGS) -I minilibx_macos
	@echo "\033[35;4m$(NAME) Ready !\033[0m"

%.o: %.c
	@gcc $(FLAG) -c $< -o $@

clean:
	make clean -C libft
	make clean -C minilibx_macos
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
