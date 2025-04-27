/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:40:31 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/23 20:39:10 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define TRUE 1
# define FALSE 0
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct flag
{
	int	space;
	int	hash;
	int	sign;
}		t_flags_printf;
void	print_unsigned_decimal(va_list args, int *count);
void	*ft_memset(void *str, int c, size_t n);
void	ft_put_unsigned_nbr(unsigned long nb, int *count);
int		ft_printf(const char *s, ...);
void	print_chars_and_ptr(va_list args, char c, int *count);
void	ft_putchar(char c, int *count);
void	ft_putstr(char *str, int *count);
void	print_numbers(va_list args, int flag_space, int flag_signe, int *count);
void	ft_putnbr(int n, int *count);
void	print_hexa(va_list args, char c, int if_flag, int *count);
void	ft_print_hexa(unsigned int nbr, int is_upper, int *count);
void	ft_print_ptr(unsigned long nbr, int is_upper, int *count);
char	*ft_strchr(const char *str, int search_str);
#endif
