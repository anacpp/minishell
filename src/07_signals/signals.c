/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/23 20:27:17 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handler for the SIGINT signal (ctrl-C).
 * * This function is called when the process receives a SIGINT.
 * It writes a new line to standard output, informs the readline library
 * that the cursor has moved, clears the current line buffer and redisplays the prompt.
 * This effectively cancels the current command line and prepares a new one.
 * * @param signo The signal number (not used,
	but required by the signature).
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
 * @brief Configures signal handlers for minishell.
 *
 * `sigaction` is used for `SIGINT` (ctrl-C) to have more
 * robust control. The `handle_sigint` handler is associated with it.
 * * `signal` with `SIG_IGN` is used for `SIGQUIT` (ctrl-\) so that
 * the shell ignores it completely in interactive mode, as bash does.
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
