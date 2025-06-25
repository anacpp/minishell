/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:14:43 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMA, VALGRIND

    DONE : NORMINETTE - OK
*/
#include "../../includes/minishell.h"

char	*generate_temp_name(int suffix)
{
	char	*base;
	char	*number;
	char	*full_path;

	base = "/tmp/minishell_heredoc_";
	number = ft_itoa(suffix);
	if (!number)
		return (NULL);
	full_path = ft_strjoin(base, number);
	free(number);
	return (full_path);
}

int	create_temp_file(char *buffer, size_t size)
{
	int		fd;
	int		suffix;
	char	*full_path;

	suffix = (int)getpid();
	while (1)
	{
		full_path = generate_temp_name(suffix++);
		if (!full_path)
			return (-1);
		if (ft_strlen(full_path) >= size)
		{
			free(full_path);
			return (-1);
		}
		ft_strcpy(buffer, full_path);
		free(full_path);
		fd = open(buffer, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
			return (fd);
		if (suffix > (int)getpid() + 1000)
			break ;
	}
	return (-1);
}