/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:12:16 by aiimdih           #+#    #+#             */
/*   Updated: 2024/12/01 17:27:43 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_(const char *str, size_t *new_pos, int search_str)
{
	unsigned char	s;
	unsigned char	*strs;
	size_t			i;

	if (str == NULL)
		return (NULL);
	i = 0;
	s = (unsigned char)search_str;
	strs = (unsigned char *)str;
	while (strs[i] && strs[i] != s)
		i++;
	*new_pos = i;
	if (strs[i] == s)
		return ((char *)strs + i);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy_(result, (char *)s, len + 1);
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned int	s_length;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start > s_length)
		return (ft_strdup(""));
	if (len > s_length - start)
		len = s_length - start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlcpy_(char *dest, const char *src, size_t size)
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
