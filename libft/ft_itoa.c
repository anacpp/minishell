/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:10:59 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/17 14:53:40 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbr(long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			number;
	long long	nb;
	char		*str;

	nb = (long long)n;
	number = count_nbr(n) - 1;
	str = (char *)ft_calloc((count_nbr(n) + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		nb = -nb;
	while (number >= 0)
	{
		str[number] = (nb % 10) + '0';
		nb = nb / 10;
		number--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
