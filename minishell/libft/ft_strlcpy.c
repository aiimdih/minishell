/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:59:04 by aiimdih           #+#    #+#             */
/*   Updated: 2025/04/05 18:36:04 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (size == 0)
	{
		return (len);
	}
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (!src)
	{
		return (0);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

char	**dup_str_array(char **src, int count)
{
	char	**dest;
	int		i;

	i = 0;
	dest = malloc((count + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (i > 0)
				free(dest[--i]);
			free(dest);
			return (NULL);
		}
		i++;
	}
	dest[count] = NULL;
	return (dest);
}
