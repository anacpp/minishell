# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 15:53:06 by acesar-p          #+#    #+#              #
#    Updated: 2024/10/26 19:17:11 by acesar-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRC = ft_putnbr.c ft_putadd.c ft_puthex.c ft_putstr.c ft_putchar.c ft_putunbr.c ft_printf.c

OBJ = $(SRC:.c=.o) 

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	
.c.o: 
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -rf $(OBJ) $(OBJBON)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
