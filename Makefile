CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR) -Iinclude
LIBS = -lreadline

SRC = \

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS)
	@echo "Linking done."

$(LIBFT):
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR)
	@echo "libft built."

.c.o:
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJ)
	#TODO: Remover depois de testar
	rm -f test/test_readline 
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

#TODO: Deletar depois de testar
test_readline:
	@echo "🔧 Compilando teste com readline..."
	$(CC) $(CFLAGS) test/test_readline.c -o test/test_readline $(LIBS)
	@echo "✅ Teste compilado: ./test/test_readline"