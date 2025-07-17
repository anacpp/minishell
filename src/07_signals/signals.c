/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/17 18:01:34 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Manipulador para o sinal SIGINT (ctrl-C).
 * * Esta função é chamada quando o processo recebe um SIGINT.
 * Ela escreve uma nova linha na saída padrão, informa à biblioteca readline
 * que o cursor se moveu, limpa o buffer de linha atual e redisplaya o prompt.
 * Isso efetivamente cancela a linha de comando atual e prepara uma nova.
 * * @param signo O número do sinal (não utilizado,
	mas exigido pela assinatura).
 */
static void	handle_sigint(int signo)
{
	g_signal_status = 130;
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Configura os manipuladores de sinal para o minishell.
 *
 * `sigaction` é usado para `SIGINT` (ctrl-C) para ter um controle mais
 * robusto. O handler `handle_sigint` é associado a ele.
 * * `signal` com `SIG_IGN` é usado para `SIGQUIT` (ctrl-\) para que
 * o shell o ignore completamente no modo interativo, como o bash faz.
 */
void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		handle_error(NULL, "sigaction failed", 1, 1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		handle_error(NULL, "signal failed", 1, 1);
}
