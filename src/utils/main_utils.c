/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:13:48 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/30 11:13:52 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_exit(int is_interactive)
{
	if (is_interactive)
		write(STDOUT_FILENO, "exit\n", 5);
}

char	*get_input(int is_interactive)
{
	if (is_interactive)
		return readline("minishell$ ");
	return readline(NULL);
}
