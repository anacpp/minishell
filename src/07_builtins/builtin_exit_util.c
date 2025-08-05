/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:19:33 by rdos-san          #+#    #+#             */
/*   Updated: 2025/08/05 17:35:09 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Libera os recursos do shell e termina o processo.
 * @param shell_context O contexto do shell para limpeza.
 * @param status O código de status para a saída.
 */
void	cleanup_and_exit(t_shell *shell_context, int status)
{
	free_environment(shell_context);
	clear_history();
	exit(status);
}

/**
 * @brief Imprime a mensagem de erro para argumento numérico inválido.
 * @param arg O argumento que causou o erro.
 */
void	exit_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}
