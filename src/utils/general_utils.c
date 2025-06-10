/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/09 01:24:22 by rjacques         ###   ########.fr       */
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
