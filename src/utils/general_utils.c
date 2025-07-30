/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/30 11:13:30 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_error(char *data, char *msg, int code, int should_exit)
{
	if (msg)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	if (data)
		free(data);
	if (should_exit)
		exit(code);
}

int	ft_lstsize(t_stack *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds != NULL)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

/**
 * @brief Prints a standardized error message for the cd command.
 *
 * @param path The path that caused the error.
 * @param msg The specific error message.
 */
void	print_cd_error(const char *path, const char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
