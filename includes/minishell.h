/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/30 10:16:22 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# ifndef MAX_PIDS
#  define MAX_PIDS 1024
# endif

# ifndef ERROR_CODE
#  define ERROR_CODE 127
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal_status;

typedef struct s_shell
{
	char						**envp;
	int							last_status;
}								t_shell;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND,
	T_ARGUMENT
}								t_token_type;

typedef struct s_token
{
	char						*value;
	t_token_type				type;
	struct s_token				*next;
	int							quote_type;
}								t_token;

typedef struct s_redir
{
	t_token_type				type;
	char						*filename;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						**argv;
	t_redir						*redirs;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_fork_ctx {
	int *pipe_fds;
	int in_fd;
	int *num_pids;
	pid_t *child_pids;
} t_fork_ctx;

typedef struct s_pipeline_ctx {
	int pipe_fds[2];
	int in_fd;
	int num_pids;
	pid_t child_pids[MAX_PIDS];
	t_fork_ctx fork_ctx;
} t_pipeline_ctx;

// Error handling functions
void							handle_error(char *data, char *msg, int code,
									int should_exit);
int								report_syntax_error(const char *message,
									t_token *token);
int								error_unexpected_token(t_token *token);

// Input functions
int								is_valid_input_syntax(const char *input);
int								is_redirect(char c);
void							update_quote_state(char c, int *in_single,
									int *in_double);

// Tokenizer functions
t_token							*tokenize_input(const char *input);
void							add_token(t_token **head, char *value,
									t_token_type type, int quote_type);
void							free_tokens(t_token *head);
char							*ft_strndup(const char *s, size_t n);
t_token_type					get_token_type(const char *str);
int								is_token_end(char c, int in_squote,
									int in_dquote);
int								is_operator_char(char c);
void							update_quote_flags(char c, int *in_squote,
									int *in_dquote);
t_token							*get_next_token(t_token *current);
int								token_is_operator(t_token *token);
void							get_token_next(const char *str, int *i,
									t_token **head);
char							*get_operator(const char *str, int *i);
char							*get_token_value(const char *str, int *i,
									int *quote_type);

// --- Parser Functions ---
t_cmd							*parse(t_token *tokens);
void							free_command_table(t_cmd *cmd_table);
int								token_is_redirection(t_token *token);
int								add_redirection(t_cmd *cmd,
									t_token **token_ptr);
char							*remove_quotes(char *str);
t_cmd							*create_new_cmd(void);
char							**ft_realloc_argv(char **argv,
									const char *new_arg);
int								ft_count_args(char **argv);
int								fill_segment_data(t_cmd *cmd, t_token **start,
									t_token *end);
int								count_segment_args(t_token *token);

// --- List utils ---
int								ft_lstsize(t_stack *lst);
int								count_cmds(t_cmd *cmds);

// --- Expander functions ---
char 						    *expand_variables(char *input, int status, int quote_type);
void							expand_tokens(t_token *tokens, int last_status);
void							update_quotes(char c, int *in_squote,
									int *in_dquote);
char							*append_expanded(char *result, char *input,
									int *i, int status);
char							*handle_dollar(char *str, int *i, int status);
char							*process_regular_char(char *result,
									char current, int *i);
char							*process_dollar_sequence(char *result,
									char *input, int *i, int status);
char							*append_char_and_advance(char *str, char c);
int execute_pipeline(t_cmd *cmds, t_shell *shell_context);
void execute_child_process(t_cmd *cmd, int *pipe_fds, int in_fd, t_shell *shell_context);
void unlink_heredocs(t_redir *redir);

// --- Pre-exec functions ---
int								create_heredoc(char *delimiter, char **temp_path);
char							*generate_temp_name(int suffix);
int								create_temp_file(char *buffer, size_t size);
char							*ft_strjoin_no_free(char *s1, char *s2);
int								**create_pipes(int total_cmds);

// --- Executor functions ---
int								executor(t_cmd *cmds, t_shell *shell_context);
void							exec_external(t_cmd *cmd,
									t_shell *shell_context);
void							save_stdio(int fds[2]);
void							restore_stdio(int fds[2]);
void							setup_redir(t_redir *redir);
void							save_pid(pid_t pid, int *num_pids, pid_t *child_pids);
void							wait_all_children(int *num_pids, pid_t *child_pids);

// --- Builtin functions ---
int								is_builtin(t_cmd *cmd);
int								run_builtin(t_cmd *cmd, t_shell *shell_context);
int								builtin_pwd(void);
int								builtin_export(char **argv,
									t_shell *shell_context);
int								builtin_unset(char **argv,
									t_shell *shell_context);
int								builtin_env(char **argv,
									t_shell *shell_context);
int								is_n_flag(char *str);
int								is_valid_key(char *key);
void							print_env_sorted(char **envp);

// --- Debug functions ---
const char						*token_type_str(t_token_type type);

// --- Signal handling functions ---
void							setup_signal_handlers(void);

// Executor utils functions
char							*ft_strjoin_triple(char *s1,
									char *s2, char *s3);
void							free_split(char **arr);

// --- Environment functions ---
void							init_shell_context(t_shell *shell_context);
void							free_environment(t_shell *shell_context);
void							add_env_var(const char *var_string,
									t_shell *shell_context);
void							remove_env_var(const char *key,
									t_shell *shell_context);
char							*get_env_value(const char *key, char **envp);

// --- Main utils functions ---
void							handle_exit(int is_interactive);
char							*get_input(int is_interactive);


// --- General utils ---
void							print_cd_error(const char *path, const char *msg);

#endif
