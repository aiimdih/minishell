/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:54:52 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/11 14:40:55 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*des;
	unsigned char	*srcs;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	des = (unsigned char *)dest;
	srcs = (unsigned char *)src;
	while (i < n)
	{
		des[i] = srcs[i];
		i++;
	}
	return (dest);
}
