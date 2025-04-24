/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:34:54 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/08 17:53:53 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

char	*gnl_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*gnl_strdup(const char *source)
{
	size_t	len;
	char	*duplicate;
	size_t	i;

	len = gnl_strlen(source);
	duplicate = (char *)malloc((len + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (i < len)
	{
		duplicate[i] = source[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*gnl_strjoin(char const *str1, char const *str2)
{
	size_t	len1;
	size_t	len2;
	char	*joined_str;
	size_t	i;

	len1 = gnl_strlen(str1);
	len2 = gnl_strlen(str2);
	joined_str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	i = -1;
	while (++i < len1)
		joined_str[i] = str1[i];
	i = -1;
	while (++i < len2)
		joined_str[len1 + i] = str2[i];
	joined_str[len1 + len2] = '\0';
	return (joined_str);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t		j;
	size_t		len_s;
	char		*substr;

	if (!s)
		return (NULL);
	len_s = gnl_strlen(s);
	if ((start + len) > len_s)
		len = len_s - start;
	if (start > len_s)
		len = 0;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	j = 0;
	while ((j < len) && s[start + j] != '\0')
	{
		substr[j] = s[start + j];
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
