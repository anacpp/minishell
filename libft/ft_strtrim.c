/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:34:54 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/08 17:53:53 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	first_set(const char *s1, const char *set)
{
	int	i;
	int	c;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		c = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
				c++;
			j++;
		}
		if (c == 0)
			return (i);
		i++;
	}
	return (i);
}

static int	last_set(const char *s1, const char *set)
{
	int	c;
	int	j;
	int	len;

	len = ft_strlen(s1);
	while (len--)
	{
		c = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[len])
				c++;
			j++;
		}
		if (c == 0)
			return (len);
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		i;
	int		first;
	int		last;

	i = 0;
	if (!s1)
		return (NULL);
	first = first_set(s1, set);
	last = last_set(s1, set);
	if (first > last)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * ((last - first) + 2));
	if (ptr == NULL)
		return (NULL);
	while (first <= last)
	{
		ptr[i] = s1[first];
		first++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
