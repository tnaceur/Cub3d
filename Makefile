NAME = cub3d
CC = gcc
FLAGS = -Wall -Wextra -Werror -I /usr/X11/include -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -g -fsanitize=address
RM = rm -rf
LIBFT = libft/libft.a

SRCS = cub.c\
		init.c\
		draw.c\
		utils.c\
		get_next_line.c\


OBJS = $(SRCS:%.c=%.o)

%.o : %.c
	$(CC) -Wall -Wextra -Werror -I /usr/X11/include -Imlx -c $< -o $@

all : $(NAME)

$(LIBFT) :
			make -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC)  $(FLAGS) $(LIBFT) $(OBJS)  -o $(NAME)


clean :
		make clean -C libft
		$(RM) $(OBJS)
fclean : clean
		make fclean -C libft
		$(RM) $(NAME)
re	: fclean all
	 make re -C libft