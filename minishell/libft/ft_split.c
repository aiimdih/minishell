/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:56:34 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/13 16:56:19 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str != '\0')
	{
		if (*str == charset)
		{
			in_word = 0;
		}
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*allocate_word(char *src, int size, char **strings, int word_pos)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (size + 1));
	if (word == NULL)
	{
		while (word_pos > 0)
			free(strings[--word_pos]);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		word[i] = src[i];
		i++;
	}
	word[size] = '\0';
	return (word);
}

static int	extract_words(char *str, char charset, char **strings)
{
	int		word_pos;
	char	*start;

	word_pos = 0;
	while (*str)
	{
		if (*str == charset)
			str++;
		else
		{
			start = str;
			while (*str && *str != charset)
				str++;
			strings[word_pos] = allocate_word(start, str - start, strings,
					word_pos);
			if (strings[word_pos] == NULL)
				return (0);
			word_pos++;
		}
	}
	strings[word_pos] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	int		words_count;
	char	**strings;

	if (!s)
		return (NULL);
	words_count = count_words((char *)s, c);
	strings = malloc((words_count + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	if (extract_words((char *)s, c, strings) == 0)
	{
		free(strings);
		return (NULL);
	}
	return (strings);
}
