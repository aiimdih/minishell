/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:52:55 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/23 20:37:55 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_chars_and_ptr(va_list args, char c, int *count)
{
	char			*str;
	unsigned long	ptr;

	if (c == 'p')
	{
		ptr = va_arg(args, unsigned long);
		if (!ptr)
			ft_putstr("(nil)", count);
		else
		{
			ft_putstr("0x", count);
			ft_print_ptr(ptr, FALSE, count);
		}
	}
	else if (c == 's')
	{
		str = va_arg(args, char *);
		ft_putstr(str, count);
	}
	else
	{
		c = va_arg(args, int);
		ft_putchar(c, count);
	}
}

void	print_numbers(va_list args, int flag_space, int flag_plus, int *count)
{
	int	num;

	num = va_arg(args, int);
	if (flag_space && num >= 0)
		ft_putchar(' ', count);
	else if (flag_plus && num >= 0)
		ft_putchar('+', count);
	ft_putnbr(num, count);
}

void	print_unsigned_decimal(va_list args, int *count)
{
	unsigned long	number;

	number = va_arg(args, unsigned int);
	ft_put_unsigned_nbr(number, count);
}

void	print_hexa(va_list args, char c, int if_flag, int *count)
{
	unsigned int	hexa;

	hexa = va_arg(args, unsigned int);
	if (hexa == 0)
		ft_print_hexa(hexa, FALSE, count);
	else if (c == 'x')
	{
		if (if_flag)
			ft_putstr("0x", count);
		ft_print_hexa(hexa, FALSE, count);
	}
	else if (c == 'X')
	{
		if (if_flag)
			ft_putstr("0X", count);
		ft_print_hexa(hexa, TRUE, count);
	}
}

char	*ft_strchr(const char *str, int search_str)
{
	unsigned char	s;
	unsigned char	*strs;
	int				i;

	s = (unsigned char)search_str;
	strs = (unsigned char *)str;
	i = 0;
	while (strs[i] && strs[i] != s)
		i++;
	if (strs[i] == s)
		return ((char *)strs + i);
	else
		return (0);
}
