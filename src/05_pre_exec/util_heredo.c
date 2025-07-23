/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_heredo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/16 16:41:15 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Este arquivo contém funções auxiliares usadas para criar arquivos temporários
	necessários no funcionamento do heredoc (<<).

	Funções:
	- create_temp_file: cria um arquivo único em /tmp usando o PID do processo.
	- generate_temp_name: monta o nome do arquivo com base no PID e um sufixo.
	- ft_strjoin_no_free: junta duas strings sem liberar a primeira.

	Usado por create_heredoc para armazenar o conteúdo digitado pelo usuário.
*/

/*
	TODO: NORMINETTE

	DONE :
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
	full_path = ft_strjoin_no_free(base, number);
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
		ft_strlcpy(buffer, full_path, size);
		free(full_path);
		fd = open(buffer, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
			return (fd);
		if (suffix > (int)getpid() + 1000)
			break ;
	}
	return (-1);
}

char	*ft_strjoin_no_free(char *s1, char *s2)
{
	char	*join;

	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcpy(join + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (join);
}
