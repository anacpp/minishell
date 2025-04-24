/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:08:55 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/26 22:01:05 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putunbr(unsigned long nbr);
int	ft_putstr(char const *str);
int	ft_putnbr(long long nbr);
int	ft_puthex(unsigned long num, char *digit);
int	ft_putchar(int c);
int	ft_putadd(void *add);
int	ft_printf(const char *format, ...);

#endif
