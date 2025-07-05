/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/30 11:27:29 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TODO :
	->CHECK NORMINETTE;
	->tirar os prints e print_tokens quando for fazer a entrega;
	->refatorar a main em funções secundárias para manter na norma (25 linhas máximo);
	
	OBS:
	-> LEAKS APENAS DA BIBLIOTECA READLINE, QUE SÃO ESPERADAS(NÃO PRECISA SE PREOCUPAR);
*/
#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	char	*trimmed_input;
	t_token	*tokens;
	t_cmd	*commands;
	int     exit_status;
	int	last_status;

	exit_status = 0;
	setup_signal_handlers();
	last_status = 0;
	while (1)
	{
		if (g_signal_status != 0)
		{
			exit_status = g_signal_status;
			g_signal_status = 0;
		}
		input = readline("minishell$ ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		trimmed_input = ft_strtrim(input, " \t\n");
		free(input);
		if (!*trimmed_input || !is_valid_input_syntax(trimmed_input))
		{
			free(trimmed_input);
			continue ;
		}
		tokens = tokenize_input(trimmed_input);
		expand_tokens(tokens, last_status);
		free(trimmed_input);
		if (!tokens)
			continue ;
		commands = parse(tokens);
		free_tokens(tokens);
		if (!commands)
			continue ;
		expand_all_variables(commands, last_status); 
		printf("\n✅ Parsing successful. Command table:\n");
		print_command_table(commands);
		printf("\n----------------------------------------\n");

		// TODO: execução

		// TODO:Remover depois de testar
		free_command_table(commands);
	}
	clear_history();
	return (exit_status);
}