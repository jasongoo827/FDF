# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 12:21:46 by jgoo              #+#    #+#              #
#    Updated: 2023/10/18 15:09:48 by jgoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS = main.c \
	   ft_printf.c \
	   ft_utils.c \
	   ft_utils2.c \
	   ft_parse.c \
	   ft_parse_utils.c \
	   ft_write_by_type.c \
	   ft_write_by_type2.c \
	   ft_write_utils.c \
	   ft_write_utils2.c \
	   ft_write_utils3.c

OBJS = $(SRCS:%.c=%.o)
INC = ft_printf.h

all: $(NAME)
	
$(NAME): $(OBJS) $(INC)
	ar rcs $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(BNS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
