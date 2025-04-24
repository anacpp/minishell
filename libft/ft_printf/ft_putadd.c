/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:00:02 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/26 21:56:11 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putadd(void *add)
{
	unsigned long	address;
	int				len;

	if (add == 0)
		return (write(1, "(nil)", 5));
	address = (unsigned long)add;
	len = 0;
	len += ft_putstr("0x");
	len += ft_puthex(address, "0123456789abcdef");
	return (len);
}
