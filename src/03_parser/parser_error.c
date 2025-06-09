/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/09 15:39:41 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Imprime uma mensagem de erro de sintaxe padronizada.
 *
 * @details Constrói e exibe uma mensagem de erro detalhada. Pode incluir
 * uma mensagem customizada e o valor do token específico que causou o erro,
 * formatado entre aspas (ex: `minishell: syntax error: `|'`).
 * Também trata o caso especial de um erro no final da linha, mostrando
 * '`newline`' como o token problemático.
 *
 * @param message A descrição principal do erro (ex: "syntax error").
 * @param error_token Opcional. O token que causou o erro. Se fornecido, seu
 * valor será incluído na mensagem. Pode ser NULL.
 * @return Retorna `0` para indicar que um erro foi reportado.
 */
int	report_syntax_error(const char *message, t_token *error_token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd((char *)message, STDERR_FILENO);
		if (error_token && error_token->value)
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error_token && error_token->value)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(error_token->value, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	else if (message && ft_strncmp(message, "syntax error", 12) == 0
		&& !error_token)
		ft_putstr_fd(" `newline'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}

/**
 * @brief Função de conveniência para reportar "token inesperado".
 *
 * @details Esta é uma função wrapper que simplifica a chamada para o erro de
 * sintaxe mais comum: "syntax error near unexpected token". Ela chama
 * `report_syntax_error` com a mensagem pré-definida.
 *
 * @param token O token que não era esperado na sequência de comando.
 * @return Retorna `0`, propagando o sinal de falha de `report_syntax_error`.
 */
int	error_unexpected_token(t_token *token)
{
	if (token)
		return (report_syntax_error("syntax error near unexpected token",
				token));
	return (report_syntax_error("syntax error near unexpected token", NULL));
}
