CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_INCLUDE = /usr/include
READLINE_LIB = /usr/lib/x86_64-linux-gnu
INCLUDES = -I$(LIBFT_DIR) -Iincludes -I$(READLINE_INCLUDE)
LIBS = -L$(READLINE_LIB) -lreadline

SRC_DIR = ./src/
SRC = $(addprefix $(SRC_DIR), \
		main.c)

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
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
