/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/22 18:52:21 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TODO: this file will no longer be necessary since pid 
globals will no longer be used*/

#include "../../includes/minishell.h"

// Defines the global variables that were declared with 'extern' in the header.
//pid_t					g_child_pids[MAX_PIDS];
//int						g_num_pids;
volatile sig_atomic_t	g_signal_status = 0;