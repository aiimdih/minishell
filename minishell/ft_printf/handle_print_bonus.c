/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_print_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:42:18 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/23 20:10:39 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *count)
{
	if (write(1, &c, 1))
		(*count)++;
}

void	ft_putnbr(int n, int *count)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		ft_putchar('-', count);
		nb *= -1;
	}
	if (nb <= 9)
	{
		nb = nb + '0';
		ft_putchar(nb, count);
	}
	else
	{
		ft_putnbr(nb / 10, count);
		ft_putnbr(nb % 10, count);
	}
}

void	ft_putstr(char *s, int *count)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], count);
		i++;
	}
}

void	ft_print_hexa(unsigned int nbr, int is_upper, int *count)
{
	char			*hexa_decimal;
	unsigned int	lenbase;

	lenbase = 16;
	if (is_upper == FALSE)
		hexa_decimal = "0123456789abcdef";
	else
		hexa_decimal = "0123456789ABCDEF";
	if (nbr < lenbase)
		ft_putchar(hexa_decimal[nbr % lenbase], count);
	else
	{
		ft_print_hexa(nbr / lenbase, is_upper, count);
		ft_print_hexa(nbr % lenbase, is_upper, count);
	}
}

void	ft_put_unsigned_nbr(unsigned long nb, int *count)
{
	if (nb <= 9)
	{
		nb = nb + '0';
		ft_putchar(nb, count);
	}
	else
	{
		ft_putnbr(nb / 10, count);
		ft_putnbr(nb % 10, count);
	}
}
