/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/17 18:27:39 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TODO :
	->CHECK NORMINETTE;
	->tirar os prints e print_tokens quando for fazer a entrega;
	->reduzir as funções > process_input e main
*/

#include "../includes/minishell.h"

/**
 * @brief Processa uma linha de comando, utilizando o contexto do shell.
 * @param input A linha de comando bruta.

	* @param shell_context O ponteiro para a struct
	que contém o estado do shell (envp,
	last_status).
 */
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
	if (!*trimmed_input || !is_valid_input_syntax(trimmed_input))
	{
		if (*trimmed_input)
			shell_context->last_status = 2;
		free(trimmed_input);
		return ;
	}
	tokens = tokenize_input(trimmed_input);
	expand_tokens(tokens, shell_context->last_status);
	free(trimmed_input);
	commands = parse(tokens);
	free_tokens(tokens);
	if (commands)
	{
		
		shell_context->last_status = executor(commands, shell_context);
		free_command_table(commands);
	}
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
		if (is_interactive)
			input = readline("minishell$ ");
		else
			input = readline(NULL);
		if (!input)
		{
			if (is_interactive)
				write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		process_input(input, &shell_context, is_interactive);
	}
	free_environment(&shell_context);
	clear_history();
	return (shell_context.last_status);
}
