NAME = libft.a
CC = ar -rcs
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isspace.c\
		ft_itoa.c\
		ft_putendl_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strcmp.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strncmp.c\


OBJS = $(SRCS:%.c=%.o)

%.o : %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(NAME) $(OBJS)


clean :
		$(RM) $(OBJS)
fclean : clean
		$(RM) $(NAME)
re	: fclean all