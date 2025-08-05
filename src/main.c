/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/08/05 17:28:09 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

/**
 * @brief Processes a command line, using the shell context.
 * @param input The raw command line.

	* @param shell_context The pointer to the struct
	that contains the shell state (envp,
	last_status).
 */
static int	should_skip_input(char *trimmed_input, t_shell *shell_context)
{
	if (!*trimmed_input || !is_valid_input_syntax(trimmed_input))
	{
		if (*trimmed_input)
			shell_context->last_status = 2;
		free(trimmed_input);
		return (1);
	}
	return (0);
}

static void	expand_and_parse(char *trimmed_input, t_token **tokens,
		t_cmd **commands, int last_status)
{
	*tokens = tokenize_input(trimmed_input);
	expand_tokens(*tokens, last_status);
	*commands = parse(*tokens);
}

static void	execute_and_cleanup(t_cmd *commands, t_shell *shell_context,
		t_token *tokens)
{
	if (commands)
	{
		shell_context->last_status = executor(commands, shell_context);
		free_command_table(commands);
	}
	free_tokens(tokens);
}

static void	process_input(char *input, t_shell *shell_context,
		int is_interactive)
{
	char	*trimmed_input;
	t_token	*tokens;
	t_cmd	*commands;

	if (is_interactive && *input)
		add_history(input);
	trimmed_input = ft_strtrim(input, " \t\n");
	free(input);
	if (should_skip_input(trimmed_input, shell_context))
		return ;
	expand_and_parse(trimmed_input, &tokens, &commands,
		shell_context->last_status);
	free(trimmed_input);
	execute_and_cleanup(commands, shell_context, tokens);
}

int	main(void)
{
	char	*input;
	t_shell	shell_context;
	int		is_interactive;

	is_interactive = isatty(STDIN_FILENO);
	init_shell_context(&shell_context);
	setup_signal_handlers();
	while (1)
	{
		if (g_signal_status != 0)
		{
			shell_context.last_status = g_signal_status;
			g_signal_status = 0;
		}
		input = get_input(is_interactive);
		if (!input)
		{
			handle_exit(is_interactive);
			break ;
		}
		process_input(input, &shell_context, is_interactive);
	}
	free_environment(&shell_context);
	clear_history();
	return (shell_context.last_status);
}
