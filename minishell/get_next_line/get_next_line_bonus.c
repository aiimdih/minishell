/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:12:52 by aiimdih           #+#    #+#             */
/*   Updated: 2024/12/02 15:47:09 by aiimdih          ###   ########.fr       */
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
	while (ft_strchr(remainder, new_pos, '\n') == NULL)
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
	static char	*remainder[OPEN_MAX];
	size_t		new_pos;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || fd >= OPEN_MAX || fd < 0)
		return (NULL);
	new_pos = 0;
	remainder[fd] = find_new_line(remainder[fd], &new_pos, fd);
	if (remainder[fd] == NULL)
		return (NULL);
	if (remainder[fd][new_pos] == '\n')
		new_pos++;
	line = ft_substr(remainder[fd], 0, new_pos);
	if (remainder[fd][new_pos])
		tmp = ft_strdup(remainder[fd] + new_pos);
	else
		tmp = NULL;
	free(remainder[fd]);
	remainder[fd] = ft_strdup(tmp);
	free(tmp);
	return (line);
}
/*
int main()
{
	char *line1;
	int fd = open("test.txt", O_RDWR);
	int fd1 = open("get_next_line.c", O_RDWR);
	
	char *line;
	line = get_next_line(fd);
	printf("%s",line);
	free(line);

	while (line1 = get_next_line(fd1))
	{
		printf("%s",line1);
		free(line1);
	}
	while (line = get_next_line(fd))
	{
		printf("%s",line);
		free(line);
	}
}*/
