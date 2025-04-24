/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:16:52 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/01 18:19:47 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	nbr;
	const char	*digits;

	digits = "0123456789";
	nbr = (long long)n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr < 10)
	{
		ft_putchar_fd(digits[nbr], fd);
		return ;
	}
	ft_putnbr_fd((nbr / 10), fd);
	ft_putchar_fd(digits[nbr % 10], fd);
}
