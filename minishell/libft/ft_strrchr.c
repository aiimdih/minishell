/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:01:12 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/11 14:29:51 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ss;
	char	cc;
	int		len;

	len = ft_strlen(s);
	ss = (char *)s;
	cc = (char)c;
	while (len && ss[len] != cc)
		len--;
	if (ss[len] != cc)
		return (0);
	else
	{
		return (ss + len);
	}
}
