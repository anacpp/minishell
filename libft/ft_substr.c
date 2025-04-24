/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:12:24 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/17 15:30:36 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		j;
	size_t		len_s;
	char		*substr;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
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
