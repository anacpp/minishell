/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/09 00:41:47 by rjacques         ###   ########.fr       */
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
	int	last_status;

	last_status = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("\n[Encerrado com Ctrl+D]\n");
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
		printf("\n✅ Parsing successful. Command table:\n");
		print_command_table(commands);
		printf("\n----------------------------------------\n");

		// TODO: execução

		// TODO:Remover depois de testar
		free_command_table(commands);
	}
	clear_history();
	return (0);
}