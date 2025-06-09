/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/16 20:14:57 by acesar-p         ###   ########.fr       */
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

void	handle_error(char *data, char *msg, int code)
{
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	if (data)
		free(data);
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