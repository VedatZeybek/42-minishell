NAME	=	minishell
LIBS	=	libft/libft.a ft_printf/libftprintf.a

SRC		=	*.c \
			*/*.c \
			*/*/*.c 

GREEN=\033[0;32m
SET_DEF=\033[0m

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
	@cc -Wall -Wextra -Werror $(SRC) $(LIBS) -o $(NAME) -lreadline -Ilibft -Ift_printf -Iincludes
	@echo "$(GREEN)Project Compiled Successfeully.$(SET_DEF)"

$(LIBS):
	@make -C libft/ all
	@make -C ft_printf/ all
	@echo "$(GREEN)Libs Compiled Successfeully.$(SET_DEF)"

clean:
	@make -C libft/ clean
	@make -C ft_printf/ clean
	@echo "$(GREEN)Project Cleaned Successfeully.$(SET_DEF)"

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@make -C ft_printf/ fclean

# T E S T S
test1: srcs/builtin/*
	rm -rf test1
	cc -Wall -Wextra -Werror srcs/builtin/*.c srcs/executor/* libft/libft.a ft_printf/libftprintf.a -Iincludes -Ilibft -Ift_printf -o test1

re: fclean all