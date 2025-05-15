#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"


typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND,
	T_ARGUMENT
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;


// Error handling functions
void handle_error(char *data, char *msg, int code);

// Input functions
void	is_valid_input_syntax(const char *input);
int	update_quote_flags(char c, int in_squote, int in_dquote);
void	is_valid_input_syntax(char *input);
int	skip_redirect_and_check_error(const char *input, int *i);
int	is_redirect(char c);
void	update_quote_state(char c, int *in_single, int *in_double);

// Tokenizer functions
t_token	*tokenize_input(const char *input);
void	add_token(t_token **head, char *value, t_token_type type);
void	free_tokens(t_token *head);
char	*ft_strndup(const char *s, size_t n);
t_token_type	get_token_type(const char *str);
int	is_token_end(char c, int in_squote, int in_dquote);
void	update_token_value(char **value, const char *expanded_value);
void	print_tokens(t_token *head);


#endif