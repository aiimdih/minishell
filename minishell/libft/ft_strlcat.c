/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:58:54 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/09 13:22:48 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	lensrc;
	size_t	lendest;
	size_t	nlen;
	size_t	i;

	i = 0;
	if (size == 0 && !dest)
		return (ft_strlen(src));
	lensrc = ft_strlen(src);
	lendest = ft_strlen(dest);
	if (!dest || !src)
		return (0);
	if (size <= lendest)
		return (lensrc + size);
	while (src[i] && lendest + i < size - 1)
	{
		dest[(lendest + i)] = src[i];
		i++;
	}
	dest[(lendest + i)] = '\0';
	nlen = lensrc + lendest;
	return (nlen);
}

size_t	ft_strcat(char *dst, const char *src)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	i;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	i = dst_length;
	while (*src)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (dst_length + src_length);
}
