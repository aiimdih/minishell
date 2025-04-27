/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:55:12 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/03 17:55:16 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
