/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:12:52 by aiimdih           #+#    #+#             */
/*   Updated: 2025/03/10 17:14:06 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s1[i])
		i++;
	while (s2[j])
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	ft_strcat(result, (char *)s1);
	ft_strcat(result, (char *)s2);
	return (result);
}

char	*find_new_line(char *remainder, size_t *new_pos, int fd)
{
	int		bytes_read;
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strchr_(remainder, new_pos, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (free(remainder), remainder = NULL, NULL);
		}
		if (bytes_read > 0)
			buffer[bytes_read] = '\0';
		else
			break ;
		tmp = remainder;
		remainder = ft_strjoin(remainder, buffer);
		free(tmp);
	}
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;
	size_t		new_pos;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	new_pos = 0;
	remainder = find_new_line(remainder, &new_pos, fd);
	if (remainder == NULL)
		return (NULL);
	if (remainder[new_pos] == '\n')
		new_pos++;
	line = ft_substr(remainder, 0, new_pos);
	if (remainder[new_pos])
		tmp = ft_strdup(remainder + new_pos);
	else
		tmp = NULL;
	free(remainder);
	remainder = ft_strdup(tmp);
	free(tmp);
	return (line);
}
/*
int main()
{
	int fd = open("test.txt", O_RDWR);
	char *line;
	while (line = get_next_line(fd))
	{
		printf("%s",line);
		free(line);
	}	
}*/
