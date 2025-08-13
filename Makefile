NAME	=	minishell
LIBS	=	libft/libft.a

SRC		=	*.c \
			*/*.c \

GREEN=\033[0;32m
SET_DEF=\033[0m

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
	@cc $(SRC) $(LIBS) -o $(NAME) -lreadline -Ilibft -Iincludes
	@echo "$(GREEN)Project Compiled Successfeully.$(SET_DEF)"

$(LIBS):
	@make -C libft/ all
	@echo "$(GREEN)Libs Compiled Successfeully.$(SET_DEF)"

clean:
	@rm -f $(NAME)
	@make -C libft/ clean
	@echo "$(GREEN)Project Cleaned Successfeully.$(SET_DEF)"

fclean: clean
	@make -C libft/ fclean

re: fclean all