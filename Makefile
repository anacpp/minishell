CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_INCLUDE = /usr/include
READLINE_LIB = /usr/lib/x86_64-linux-gnu
INCLUDES = -I$(LIBFT_DIR) -Iincludes -I$(READLINE_INCLUDE)
LIBS = -L$(READLINE_LIB) -lreadline

SRC_DIR = ./src/

INPUTS_DIR = $(SRC_DIR)/01_inputs
TOKEN_DIR = $(SRC_DIR)/02_token
PARSER_DIR = $(SRC_DIR)/03_parser
SIGNALS_DIR = $(SRC_DIR)/07_signals
UTILS_DIR = $(SRC_DIR)/utils
EXPANDER_DIR = $(SRC_DIR)/04_expander

SRC = 	$(SRC_DIR)/main.c \
		$(INPUTS_DIR)/input_minishell.c \
		$(INPUTS_DIR)/utils_input.c \
		$(TOKEN_DIR)/tokenizer.c \
		$(TOKEN_DIR)/utils_token.c \
		$(TOKEN_DIR)/utils_token2.c \
		$(TOKEN_DIR)/utils_token3.c \
		$(PARSER_DIR)/parser.c \
		$(PARSER_DIR)/parser_cleanup.c \
		$(PARSER_DIR)/parser_error.c \
		$(PARSER_DIR)/parser_helpers.c \
		$(PARSER_DIR)/parser_print_test.c \
		$(PARSER_DIR)/parser_print_test.c \
		$(PARSER_DIR)/parser_redirect.c \
		$(PARSER_DIR)/parser_rules.c \
		$(PARSER_DIR)/parser_segment_args.c \
		$(PARSER_DIR)/parser_utils.c \
		$(SIGNALS_DIR)/signals.c \
		$(UTILS_DIR)/general_utils.c
		$(PARSER_DIR)/parser_rules.c \
		$(PARSER_DIR)/parser_segment_args.c \
		$(PARSER_DIR)/parser_utils.c \
		$(UTILS_DIR)/general_utils.c \
		$(EXPANDER_DIR)/expand_all.c \
		$(EXPANDER_DIR)/expander.c \
		$(EXPANDER_DIR)/utils_expand.c

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
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Cleaning test temporary files..."
	@$(RM) tests/stderr.tmp

re: fclean all

.PHONY: all clean fclean re test

test: all
	@echo "Running built-in tests..."
	@bash tests/test_builtin.sh || true
	@echo "\nRunning execution tests..."
	@bash tests/test_execution.sh || true
	@echo "Running built-in tests..."
	@bash tests/test_builtin.sh || true
	@echo "\nRunning execution tests..."
	@bash tests/test_execution.sh || true
	@echo "\nRunning expansion tests..."
	@bash tests/test_expansion.sh || true
	@echo "\nRunning pipes and redirection tests..."
	@bash tests/test_pipes_and_redirs_exec.sh || true
	@echo "\nRunning parser tests..."
	@bash tests/test_parser.sh || true

	@echo "\nRunning pipes and redirection tests..."
	@bash tests/test_pipes_and_redirs_exec.sh || true
	@echo "\nRunning parser tests..."
	@bash tests/test_parser.sh || true

