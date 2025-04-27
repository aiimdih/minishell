/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:57:18 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/11 14:29:32 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
