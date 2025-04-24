/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:01:19 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/26 21:06:16 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long num, char *digit)
{
	int	len;

	len = 0;
	if (num > 15)
		len += ft_puthex(num / 16, digit);
	len += write(1, &digit[num % 16], 1);
	return (len);
}
