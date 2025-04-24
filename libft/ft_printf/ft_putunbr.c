/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:19:20 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/26 21:07:24 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned long nbr)
{
	char	*digit;
	int		len;

	digit = "0123456789";
	len = 0;
	if (nbr > 9)
		len += ft_putunbr(nbr / 10);
	len += write(1, &digit[nbr % 10], 1);
	return (len);
}
