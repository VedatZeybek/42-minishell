NAME = libftprintf.a
SRCS = ft_printf.c \
	ft_putstr.c \
	ft_putchar.c \
	ft_putnbr.c \
	ft_putunsigned.c \
	ft_putnbr_base.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@cc -Wall -Wextra -Werror -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all