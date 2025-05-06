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
# include "libft.h"


typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;


// Error handling functions
void	handle_error(const char *msg, const char *input, int exit_code);

// Tokenizer functions
t_token	*tokenize_input(const char *input);
void	add_token(t_token **head, char *value, t_token_type type);
void	free_tokens(t_token *head);
char	*ft_strndup(const char *s, size_t n);


#endif