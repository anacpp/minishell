/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/10 02:15:28 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO : CHECK NORMINETTE

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND,
	T_ARGUMENT
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

// Error handling functions
void				handle_error(char *data, char *msg, int code,
						int should_exit);
int					report_syntax_error(const char *message, t_token *token);
int					error_unexpected_token(t_token *token);

// Input functions
int					is_valid_input_syntax(const char *input);
int					skip_redirect_and_check_error(const char *input, int *i);
int					is_redirect(char c);
void				update_quote_state(char c, int *in_single, int *in_double);

// Tokenizer functions
t_token				*tokenize_input(const char *input);
t_token				*get_last_token(t_token *head);
void				add_token(t_token **head, char *value, t_token_type type);
void				free_tokens(t_token *head);
char				*ft_strndup(const char *s, size_t n);
t_token_type		get_token_type(const char *str);
int					is_token_end(char c, int in_squote, int in_dquote);
void				update_token_value(char **value, char *expanded_value);
int					is_operator_char(char c);
void				update_quote_flags(char c, int *in_squote, int *in_dquote);
int					is_heredoc_context(t_token *last);
char				*handle_char(const char *str, int *i);
t_token				*get_next_token(t_token *current);
int					token_is_operator(t_token *token);

// --- NOVAS FUNÇÕES DO PARSER ---
t_cmd				*parse(t_token *tokens);
void				free_command_table(t_cmd *cmd_table);
void	print_command_table(t_cmd *cmds); // Para depuração
int					token_is_redirection(t_token *token);
int					add_redirection(t_cmd *cmd, t_token **token_ptr);
char				*remove_quotes(char *str);
t_cmd				*create_new_cmd(void);
char				**ft_realloc_argv(char **argv, const char *new_arg);

// Funções de depuração para impressão de tokens, APAGAR QUANDO FOR ENTREGAR
void				print_tokens(t_token *head);
const char			*token_type_str(t_token_type type);
#endif
