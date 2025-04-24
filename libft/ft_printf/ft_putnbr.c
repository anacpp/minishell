/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:56:50 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/26 21:08:28 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long long nbr)
{
	char const	*digit;
	int			len;

	len = 0;
	digit = "0123456789";
	if (nbr < 0)
	{
		len += write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
		len += ft_putnbr(nbr / 10);
	len += write(1, &digit[nbr % 10], 1);
	return (len);
}
