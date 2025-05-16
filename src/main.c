/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/16 20:14:24 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TODO : 
    ->CHECK NORMINETTE;
	->tirar os prints e print_tokens quando for fazer a entrega;
    ->refatorar a main em funções secundárias para manter na norma (25 linhas máximo);
	->adicionar tratamento para quando o input escrito não corresponder a nenhum tipo de comando externo ou interno; retuornar erro : comando não encontrado;

	OBS:
	-> LEAKS APENAS DA BIBLIOTECA READLINE, QUE SÃO ESPERADAS(NÃO PRECISA SE PREOCUPAR);
*/
#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	char	*pre_treat_input;
	t_token	*tokens;

	printf("Digite algo (Ctrl+D para sair):\n");
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
		printf("Você digitou: %s\n", input);
		pre_treat_input = ft_strtrim((char *)input, " \t\n");
		free(input);
		if (!*pre_treat_input)
		{
			free(pre_treat_input);
			continue ;
		}
		is_valid_input_syntax(pre_treat_input);
		tokens = tokenize_input(pre_treat_input);
		free(pre_treat_input);
		if (!tokens)
			continue ;
		print_tokens(tokens);
		free_tokens(tokens);
	}
	clear_history();
	return (0);
}
