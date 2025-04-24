/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:56:27 by acesar-p          #+#    #+#             */
/*   Updated: 2024/11/01 15:39:51 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_verifier(const char *format, va_list args, int *len)
{
	if (*format == '%')
		*len += ft_putchar('%');
	else if (*format == 'c')
		*len += ft_putchar((char)va_arg(args, int));
	else if (*format == 's')
		*len += ft_putstr(va_arg(args, char *));
	else if (*format == 'p')
		*len += ft_putadd((void *)va_arg(args, unsigned long));
	else if (*format == 'd' || *format == 'i')
		*len += ft_putnbr(va_arg(args, int));
	else if (*format == 'u')
		*len += ft_putunbr(va_arg(args, unsigned int));
	else if (*format == 'x')
		*len += ft_puthex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (*format == 'X')
		*len += ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else
		*len += ft_putchar(*format);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	len = 0;
	while (*format != '\0')
	{
		if (*format == '%' && !*(format + 1))
			break ;
		if (*format == '%')
		{
			format++;
			ft_verifier(format, args, &len);
		}
		else
			len += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (len);
}
