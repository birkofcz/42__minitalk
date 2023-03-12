# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/05 11:25:26 by sbenes            #+#    #+#              #
#    Updated: 2023/03/06 14:56:46 by sbenes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

#sources
SRC = ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putptr.c ft_puthex.c ft_putunsigned.c
OBJ = $(SRC:.c=.o)
NAME = libftprintf.a

#clean
RM = rm -f

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) 
	$(AR) $(NAME) $(OBJ)
	

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
