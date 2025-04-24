/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:41:28 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/26 21:41:45 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char const *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
	{
		len += write(1, "(null)", 6);
		return (len);
	}
	while (str[i] != '\0')
	{
		len += write(1, &str[i], 1);
		i++;
	}
	return (len);
}
