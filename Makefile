NAME	=	minishell
LIBS	=	libft/libft.a

SRC		=	*.c \
			*/*.c \
			*/*/*.c 

GREEN=\033[0;32m
SET_DEF=\033[0m

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
	@cc -Wall -Wextra -Werror $(SRC) $(LIBS) -o $(NAME) -lreadline -Ilibft -Iincludes
	@echo "$(GREEN)Project Compiled Successfeully.$(SET_DEF)"

$(LIBS):
	@make -C libft/ all
	@echo "$(GREEN)Libs Compiled Successfeully.$(SET_DEF)"

clean:
	@make -C libft/ clean
	@echo "$(GREEN)Project Cleaned Successfeully.$(SET_DEF)"

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

# T E S T S
test1: srcs/builtin/*.c srcs/executor/*.c $(LIBS)
	rm -rf test1
	cc -Wall -Wextra -Werror srcs/builtin/*.c srcs/executor/*.c $(LIBS) -Iincludes -Ilibft -Ift_printf -o test1
	make fclean

re: fclean all

.PHONY: all fclean clean re test1