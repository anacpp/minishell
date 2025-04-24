/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:34:54 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/08 17:53:53 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_append(int fd, char *buffer, char *saved_text)
{
	int		bytes_read;
	char	*temp_storage;

	bytes_read = 1;
	while (!ft_strchr(saved_text, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(saved_text);
			return (NULL);
		}
		if (bytes_read == 0 && saved_text[0] == '\0')
		{
			free(saved_text);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp_storage = saved_text;
		saved_text = ft_strjoin(saved_text, buffer);
		free(temp_storage);
		if (!saved_text)
			return (NULL);
	}
	return (saved_text);
}

static void	update_saved_text(char **saved_text, int newline_index)
{
	char	*temp_storage;
	size_t	length;
	size_t	i;

	length = ft_strlen(*saved_text + newline_index + 1);
	temp_storage = (char *)malloc((length + 1) * sizeof(char));
	if (!temp_storage)
	{
		free(*saved_text);
		*saved_text = NULL;
		return ;
	}
	i = 0;
	while ((*saved_text)[newline_index + 1 + i])
	{
		temp_storage[i] = (*saved_text)[newline_index + 1 + i];
		i++;
	}
	temp_storage[i] = '\0';
	free(*saved_text);
	*saved_text = temp_storage;
}

static char	*extract_next_line(char **saved_text)
{
	int		newline_index;
	char	*line;

	newline_index = 0;
	while ((*saved_text)[newline_index] && (*saved_text)[newline_index] != '\n')
		newline_index++;
	line = ft_substr(*saved_text, 0,
			newline_index + ((*saved_text)[newline_index] == '\n'));
	if (!line)
	{
		free(*saved_text);
		*saved_text = NULL;
		return (NULL);
	}
	if ((*saved_text)[newline_index] == '\n')
		update_saved_text(saved_text, newline_index);
	else
	{
		free(*saved_text);
		*saved_text = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved_text[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!saved_text[fd])
		saved_text[fd] = ft_strdup("");
	saved_text[fd] = read_and_append(fd, buffer, saved_text[fd]);
	free(buffer);
	if (!saved_text[fd])
		return (NULL);
	line = extract_next_line(&saved_text[fd]);
	if (!line && saved_text[fd])
	{
		free(saved_text[fd]);
		saved_text[fd] = NULL;
	}
	return (line);
}
