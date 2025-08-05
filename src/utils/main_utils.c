/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:13:48 by rdos-san          #+#    #+#             */
/*   Updated: 2025/08/05 17:33:12 by rdos-san         ###   ########.fr       */
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
	return (readline(NULL));
}
