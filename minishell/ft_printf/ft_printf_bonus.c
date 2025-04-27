/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:42:07 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/23 15:29:18 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_if_specifier(const char *s)
{
	while (*s)
	{
		if (ft_strchr("scxXidpu%", *s))
			return (TRUE);
		else if (ft_strchr(" +#", *s))
			s++;
		else
			return (FALSE);
	}
	return (FALSE);
}

void	check_flags(char **format, t_flags *flags)
{
	while (**format)
	{
		if (**format == ' ')
		{
			if (flags->sign == 0)
				flags->space = TRUE;
		}
		else if (**format == '+')
		{
			flags->sign = TRUE;
			flags->space = FALSE;
		}
		else if (**format == '#')
			flags->hash = TRUE;
		else
			return ;
		(*format)++;
	}
}

void	handle_specifier(char specifier, va_list args, t_flags *flags,
		int *count)
{
	if ((specifier == 's' || specifier == 'c'))
		print_chars_and_ptr(args, specifier, count);
	else if (specifier == 'd' || specifier == 'i')
		print_numbers(args, flags->space, flags->sign, count);
	else if (specifier == 'x' || specifier == 'X')
		print_hexa(args, specifier, flags->hash, count);
	else if (specifier == '%')
		ft_putchar('%', count);
	else if (specifier == 'p')
		print_chars_and_ptr(args, specifier, count);
	else if (specifier == 'u')
		print_unsigned_decimal(args, count);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	const char	*ptr;
	int			count;
	t_flags		flags;

	if (!s)
		return (-1);
	va_start(args, s);
	count = 0;
	ptr = s;
	while (*ptr != '\0')
	{
		if (*ptr == '%' && check_if_specifier(ptr + 1) == TRUE)
		{
			ft_memset(&flags, 0, sizeof(flags));
			ptr++;
			check_flags((char **)&ptr, &flags);
			handle_specifier(*ptr, args, &flags, &count);
		}
		else
			ft_putchar(*ptr, &count);
		ptr++;
	}
	va_end(args);
	return (count);
}
