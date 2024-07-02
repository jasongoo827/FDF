# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 09:56:50 by jgoo              #+#    #+#              #
#    Updated: 2024/02/13 09:56:53 by jgoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME = fdf

CC = cc

CFLAGS = -Wall -Werror -Wextra

CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx

RM = rm -f

SRCS = main.c error.c parse.c parse_utils.c utils.c utils2.c transform_matrix.c matrix_utils.c draw_image.c vector.c bresenham.c \
mlx_hook.c rotation.c rotation_utils.c

BNS_SRCS = $(BNS_DIR)/main_bonus.c $(BNS_DIR)/error_bonus.c $(BNS_DIR)/parse_bonus.c $(BNS_DIR)/parse_utils_bonus.c $(BNS_DIR)/utils_bonus.c $(BNS_DIR)/utils2_bonus.c $(BNS_DIR)/transform_matrix_bonus.c $(BNS_DIR)/matrix_utils_bonus.c \
$(BNS_DIR)/draw_image_bonus.c $(BNS_DIR)/vector_bonus.c $(BNS_DIR)/bresenham_bonus.c $(BNS_DIR)/mlx_hook_bonus.c $(BNS_DIR)/rotation_bonus.c $(BNS_DIR)/rotation_utils_bonus.c

SRCS_LIB = $(SUB_LIBDIR)/ft_isalpha.c $(SUB_LIBDIR)/ft_isdigit.c $(SUB_LIBDIR)/ft_isalnum.c $(SUB_LIBDIR)/ft_isascii.c \
$(SUB_LIBDIR)/ft_isprint.c $(SUB_LIBDIR)/ft_strlen.c $(SUB_LIBDIR)/ft_memset.c $(SUB_LIBDIR)/ft_bzero.c \
$(SUB_LIBDIR)/ft_memcpy.c $(SUB_LIBDIR)/ft_memmove.c $(SUB_LIBDIR)/ft_strlcpy.c $(SUB_LIBDIR)/ft_strlcat.c \
$(SUB_LIBDIR)/ft_toupper.c $(SUB_LIBDIR)/ft_tolower.c $(SUB_LIBDIR)/ft_strchr.c $(SUB_LIBDIR)/ft_strrchr.c \
$(SUB_LIBDIR)/ft_strncmp.c $(SUB_LIBDIR)/ft_memchr.c $(SUB_LIBDIR)/ft_memcmp.c $(SUB_LIBDIR)/ft_strnstr.c \
$(SUB_LIBDIR)/ft_atoi.c $(SUB_LIBDIR)/ft_calloc.c $(SUB_LIBDIR)/ft_strdup.c $(SUB_LIBDIR)/ft_substr.c \
$(SUB_LIBDIR)/ft_strjoin.c $(SUB_LIBDIR)/ft_strtrim.c $(SUB_LIBDIR)/ft_split.c $(SUB_LIBDIR)/ft_itoa.c \
$(SUB_LIBDIR)/ft_strmapi.c $(SUB_LIBDIR)/ft_striteri.c $(SUB_LIBDIR)/ft_putchar_fd.c $(SUB_LIBDIR)/ft_putstr_fd.c \
$(SUB_LIBDIR)/ft_putendl_fd.c $(SUB_LIBDIR)/ft_putnbr_fd.c $(SUB_LIBDIR)/ft_lstnew.c $(SUB_LIBDIR)/ft_lstadd_front.c \
$(SUB_LIBDIR)/ft_lstsize.c $(SUB_LIBDIR)/ft_lstlast.c $(SUB_LIBDIR)/ft_lstadd_back.c $(SUB_LIBDIR)/ft_lstdelone.c \
$(SUB_LIBDIR)/ft_lstclear.c $(SUB_LIBDIR)/ft_lstiter.c $(SUB_LIBDIR)/ft_lstmap.c 

SRCS_GNL = $(SUB_GNLDIR)/get_next_line.c $(SUB_GNLDIR)/get_next_line_utils.c 

SUB_LIB = libft.a
SUB_LIBDIR = ./Libft/libft
SUB_GNL = libftgnl.a
SUB_GNLDIR = ./Libft/gnl
BNS_DIR = ./bonus
SUB_MLXDIR = ./mlx

OBJS = $(SRCS:%.c=%.o)
INC = fdf.h
BNS_OBJS = $(BNS_SRCS:%.c=%.o)
BNS_INC = bonus/fdf_bonus.h

ifdef ADD_BNS
	OBJS := $(BNS_OBJS)
	INC := $(BNS_INC)
endif

all: $(NAME)

bonus: 
	@ADD_BNS=1 make

$(NAME): $(OBJS) $(SUB_LIBDIR)/$(SUB_LIB) $(SUB_GNLDIR)/$(SUB_GNL) $(INC)
	make -C $(SUB_MLXDIR)
	$(CC) $(CFLAGS) $(CLIB) -o $(NAME) $(OBJS) -I$(SUB_LIBDIR) $(SUB_LIBDIR)/$(SUB_LIB) -I$(SUB_GNLDIR) $(SUB_GNLDIR)/$(SUB_GNL)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

$(SUB_LIBDIR)/$(SUB_LIB) : $(SRCS_LIB)
	make -C $(SUB_LIBDIR)

$(SUB_GNLDIR)/$(SUB_GNL) : $(SRCS_GNL)
	make -C $(SUB_GNLDIR)

%.o	: %.c
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	make -C $(SUB_LIBDIR) clean
	make -C $(SUB_GNLDIR) clean
	make -C $(SUB_MLXDIR) clean
	$(RM) $(OBJS) $(BNS_OBJS)

fclean: clean
	make -C $(SUB_LIBDIR) fclean
	make -C $(SUB_GNLDIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
