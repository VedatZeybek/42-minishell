NAME	=	minishell
LIBS	=	libft/libft.a

SRC		=	srcs/builtin/arg_count.c \
			srcs/builtin/ft_cd.c \
			srcs/builtin/ft_echo.c \
			srcs/builtin/ft_env.c \
			srcs/builtin/ft_exit.c \
			srcs/builtin/ft_export.c \
			srcs/builtin/ft_pwd.c \
			srcs/builtin/ft_unset.c \
			srcs/executor/ft_builtin_utils.c \
			srcs/executor/ft_cmd_exec.c \
			srcs/executor/ft_exec_cmds.c \
			srcs/executor/ft_exec_utils.c \
			srcs/executor/ft_executor.c \
			srcs/executor/ft_redirections.c \
			srcs/executor/ft_heredoc.c \
			srcs/executor/ft_run_external_command.c \
			srcs/executor/ft_vars_utils.c \
			srcs/input/free_utils.c \
			srcs/input/read_line.c \
			srcs/lexer/create_and_add_token.c \
			srcs/lexer/lexer_utils.c \
			srcs/lexer/token_redirect.c \
			srcs/lexer/tokenizer.c \
			srcs/lexer/token_word_quote.c \
			srcs/parser/command_parser.c \
			srcs/parser/create_and_add_command.c \
			srcs/parser/free_utils.c \
			main.c


GREEN=\033[0;32m
SET_DEF=\033[0m

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
	@cc -Wall -Wextra -Werror $(SRC) $(LIBS) -o $(NAME) -lreadline -Ilibft -Ift_printf -Iincludes
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
tester:
	rm -rf minishell_tester
	git clone https://github.com/LucasKuhn/minishell_tester.git

test1: srcs/builtin/*.c srcs/executor/*.c $(LIBS)
	rm -rf test1
	cc -Wall -Wextra -Werror srcs/builtin/*.c srcs/executor/*.c $(LIBS) -Iincludes -Ilibft -Ift_printf -o test1
	make fclean

re: fclean all

.PHONY: all fclean clean re test1