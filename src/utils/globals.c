/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/17 18:05:04 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TODO: esse arquivo não será mais necesário já que as globais de pid
não serão mais utilizadas*/

#include "../../includes/minishell.h"

// Define as variáveis globais que foram declaradas com 'extern' no header.
pid_t					g_child_pids[MAX_PIDS];
int						g_num_pids;
volatile sig_atomic_t	g_signal_status = 0;