# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelusine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 18:18:46 by jelusine          #+#    #+#              #
#    Updated: 2018/12/12 22:25:39 by jelusine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCC =	ft_abs.c\
		ft_analyse_base.c\
		ft_atoi.c\
		ft_atoi_base.c\
		ft_bzero.c\
		ft_charcmpstr.c\
		ft_charcolor.c\
		ft_color.c\
		ft_errormsg.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_itoa_base.c\
		ft_lstadd.c\
		ft_lstaddend.c\
		ft_lstdel.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_lst_remove_if.c\
		ft_lst_remove_if_size.c\
		ft_max.c\
		ft_memalloc.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memdel.c\
		ft_memmove.c\
		ft_memset.c\
		ft_min.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putendl.c\
		ft_putendl_fd.c\
		ft_putnbr.c\
		ft_putnbr_base.c\
		ft_putnbr_fd.c\
		ft_putstr.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strclr.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strequ.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlen.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strncat.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strsplit.c\
		ft_strstr.c\
		ft_strsub.c\
		ft_strtrim.c\
		ft_swap.c\
		ft_tolower.c\
		ft_toupper.c\
		get_next_line.c

LAG = -Wall -Werror -Wextra

SRCO = $(SRCC:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(SRCO)
	@ar rcs $@ $(SRCO)
	@echo "\033[32m$(NAME) Ready !\033[0m\n"

%.o: %.c
	@gcc $(LAG) -c $<

clean:
	@echo "\033[31mLibft: Obj Deleted\033[0m\n"
	@rm -rf $(SRCO)

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31m$(NAME) Deleted\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
