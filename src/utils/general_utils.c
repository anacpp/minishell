/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/16 16:39:32 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TODO: comment to test manually ->
(void)data;
(void)code;
Comment -> if(data) to exit(code) lines to test manually

	OBS:
	-> NORMINETTE - OK
*/

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
	int count;

	count = 0;
	while (cmds != NULL)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}