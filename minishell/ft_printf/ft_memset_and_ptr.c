/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:04:08 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/23 20:56:02 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	s;
	char			*strs;
	size_t			i;

	s = (unsigned char)c;
	strs = (char *)str;
	i = 0;
	while (i < n)
	{
		strs[i] = s;
		i++;
	}
	return (str);
}

void	ft_print_ptr(unsigned long nbr, int is_upper, int *count)
{
	char			*hexa_decimal;
	unsigned long	lenbase;

	lenbase = 16;
	if (is_upper == FALSE)
		hexa_decimal = "0123456789abcdef";
	else
		hexa_decimal = "0123456789ABCDEF";
	if (nbr < lenbase)
		ft_putchar(hexa_decimal[nbr % lenbase], count);
	else
	{
		ft_print_ptr(nbr / lenbase, is_upper, count);
		ft_print_ptr(nbr % lenbase, is_upper, count);
	}
}
