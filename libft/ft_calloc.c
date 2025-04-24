/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:10:50 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/03 16:11:58 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nmemb * size;
	if (nmemb != 0 && (total / nmemb != size))
		return (NULL);
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	else
		ft_bzero(ptr, total);
	return (ptr);
}
