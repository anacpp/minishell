# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Name of the final executable
NAME = minishell

# Command to remove files
RM = rm -f

# Define all your source files here
SRCS = src/main.c \
       src/01_inputs/input_minishell.c \
       src/01_inputs/utils_input.c \
       src/02_token/token_mutations.c \
       src/02_token/token_utils.c \
       src/02_token/token_validations.c \
       src/02_token/tokenizer.c \
       src/03_parser/parser.c \
       src/03_parser/parser_cleanup.c \
       src/03_parser/parser_error.c \
       src/03_parser/parser_helpers.c \
       src/03_parser/parser_redirect.c \
       src/03_parser/parser_rules.c \
       src/03_parser/parser_segment_args.c \
       src/03_parser/parser_utils.c \
       src/04_expander/expander.c \
       src/04_expander/utils_expand.c \
       src/04_expander/utils_expand_2.c \
       src/05_pre_exec/heredoc.c \
       src/05_pre_exec/pipe_create.c \
       src/05_pre_exec/util_heredo.c \
       src/06_executor/exec.c \
       src/06_executor/external_cmd.c \
       src/06_executor/utils_exec.c \
       src/06_executor/utils_extern_cmd.c \
       src/06_executor/utils_fork_process.c \
       src/06_executor/pipeline.c \
       src/06_executor/child_process.c \
       src/07_signals/signals.c \
       src/07_builtins/builtin.c \
       src/07_builtins/builtin_commands.c \
       src/07_builtins/builtin_exit_util.c \
       src/07_builtins/builtin_utils.c \
       src/08_environment/env_manager.c \
       src/08_environment/env_manager_utils.c \
       src/utils/general_utils.c \
       src/utils/main_utils.c

# Automatically generate object file names from source files
OBJS = ${SRCS:.c=.o}

# Header file directory
INCLUDES = -I includes -I libft

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Readline library
LDFLAGS = -lreadline

# --- Rules ---

all: $(NAME)

# Rule to link everything together
$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS)
	@echo "$(NAME) is ready!"

# Rule for libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Generic rule to compile .c files into .o files
%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rules
clean:
	@echo "Cleaning object files..."
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
