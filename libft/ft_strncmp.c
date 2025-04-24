/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:02:03 by acesar-p          #+#    #+#             */
/*   Updated: 2025/03/25 19:51:50 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	uc_s1;
	unsigned char	uc_s2;

	index = 0;
	while (index < n)
	{
		uc_s1 = (unsigned char)s1[index];
		uc_s2 = (unsigned char)s2[index];
		if (uc_s1 != uc_s2)
			return (uc_s1 - uc_s2);
		if (uc_s1 == '\0' || uc_s2 == '\0')
			break ;
		index++;
	}
	return (0);
}

