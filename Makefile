NAME	=	minishell

CC		=	cc
CFLAGS	=	#-Wall -Wextra -Werror

SRC		=	main.c ./input/read_line.c \
			executor/get_cmd_path.c executor/error.c \
			executor/executor.c 

OBJ		= $(SRC:.c=.o)

LIBFT		= ./inc/libft/libft.a
LIBFT_DIR	= ./inc/libft


READLINE_LIB = -lreadline

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_LIB) -c $< -o $@

$(LIBFT):
	@echo "Libft files compiling..."
	@$(MAKE) -s -C $(LIBFT_DIR) all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
