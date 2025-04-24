/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:14:45 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/08 17:30:21 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_substr(const char *s, char c)
{
	int	i;
	int	count_sub;
	int	in_substring;

	i = 0;
	count_sub = 0;
	in_substring = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_substring == 0)
		{
			count_sub++;
			in_substring = 1;
		}
		else if (s[i] == c && in_substring == 1)
		{
			in_substring = 0;
		}
		i++;
	}
	return (count_sub);
}

static char	*allocate_word(const char *s, char c)
{
	int		lenght;
	char	*arr;
	int		i;

	lenght = 0;
	i = 0;
	while (s[lenght] != '\0' && s[lenght] != c)
		lenght++;
	arr = (char *)malloc((lenght + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (i < lenght)
	{
		arr[i] = s[i];
		i++;
	}
	arr[lenght] = '\0';
	return (arr);
}

static void	free_all(char **matrix, int i)
{
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	matrix = (char **)malloc(sizeof(char *) * (c_substr(s, c) + 1));
	if (!matrix)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			matrix[i] = allocate_word(s, c);
			if (!(matrix[i++]))
				return (free_all(matrix, i - 1), NULL);
			while (*s && *s != c)
				s++;
		}
	}
	return (matrix[i] = NULL, matrix);
}
