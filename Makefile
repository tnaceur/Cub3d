# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 21:30:51 by abelkhad          #+#    #+#              #
#    Updated: 2023/03/08 15:09:57 by tnaceur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror 

MFLAGS = -I /usr/X11/include -l mlx -framework OpenGL -framework AppKit 

RM = rm -rf


PARSINGSRC = parsing/ft_check_char.c \
			parsing/ft_check_error.c \
			parsing/ft_dup.c \
			parsing/ft_extension.c \
			parsing/ft_fill_struct.c \
			parsing/ft_free.c \
			parsing/ft_join.c \
			parsing/ft_len.c \
			parsing/ft_map.c \
			parsing/ft_map_1.c \
			parsing/ft_prints.c \
			parsing/ft_put_error.c \
			parsing/ft_read_mapfile.c \
			parsing/ft_rgb.c \
			parsing/ft_strsplit.c \
			parsing/ft_strstr.c \
			parsing/ft_sub.c \
			parsing/ft_xpm.c

SRCS =	cub.c\
		init.c\
		draw.c\
		draw_utils.c\
		draw_utils2.c\
		utils.c\
		ft_split.c\
		ft_strjoin.c\
		ft_strlcpy.c\
		ft_strlen.c\

SRCS +=  $(PARSINGSRC)

OBJS = $(SRCS:%.c=%.o)

%.o : %.c
	$(CC) $(FLAGS) -I /usr/X11/include -Imlx -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS) cub.h parsing/parsing.h
	$(CC) $(FLAGS) $(MFLAGS) $(OBJS)  -o $(NAME)


clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re	: fclean all

.PHONY: all clean fclean re