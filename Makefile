NAME = cub3d
CC = gcc
FLAGS = -Wall -Wextra -Werror -I /usr/X11/include -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit
RM = rm -rf

SRCS = cub.c\
		init.c\
		get_next_line.c\
		libft/ft_atoi.c\
		libft/ft_bzero.c\
		libft/ft_calloc.c\
		libft/ft_isalnum.c\
		libft/ft_isalpha.c\
		libft/ft_isdigit.c\
		libft/ft_isspace.c\
		libft/ft_itoa.c\
		libft/ft_putendl_fd.c\
		libft/ft_putstr_fd.c\
		libft/ft_split.c\
		libft/ft_strchr.c\
		libft/ft_strcmp.c\
		libft/ft_strdup.c\
		libft/ft_strjoin.c\
		libft/ft_strlcpy.c\
		libft/ft_strlen.c\
		libft/ft_strncmp.c\


OBJS = $(SRCS:%.c=%.o)

%.o : %.c
	$(CC) -Wall -Wextra -Werror -I /usr/X11/include -Imlx -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	$(CC)  $(FLAGS) $(LIBFT) $(OBJS)  -o $(NAME)


clean :
		$(RM) $(OBJS)
fclean : clean
		$(RM) $(NAME)
re	: fclean all