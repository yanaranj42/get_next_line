/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:52:58 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/19 13:32:14 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free(s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(s2);
		*s2 = NULL;
	}
	return (NULL);
}

static char	*ft_next(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	printf("%s", buffer);
	if (!buffer)
	{
		ft_free(&buffer, NULL);
		return (NULL);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
	{
		line[j] = buffer[i];
		j++;
		i++;
	}
	ft_free(&buffer, NULL);
	return (line);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(BUFFER_SIZE +1, sizeof(char));
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_file(int fd, char *strg)
{
	char	*buffer;
	int		bytes;

	if (!strg)
		strg = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (ft_free(&strg, NULL));
	bytes = 1;
	while (bytes > 0 && ft_strchr(buffer, '\n'))
	{
		bytes = read (fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (bytes > 0)
		{
			buffer[bytes] = 0;
			strg = ft_strjoin(strg, buffer);
			if (!strg)
				return (NULL);
		}
		return (ft_free(&buffer, &strg));
	}
	return (strg);
}

char	*get_next_line(int fd)
{
	static char	*strg = NULL;
	char		*line;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	strg = read_file(fd, strg);
	printf("%s\n", strg);
	if (!strg)
		return (NULL);
	line = ft_line(strg);
	strg = ft_next(strg);
	if (!line || !strg)
		return (NULL);
	printf("line: %s\n", line);
	return (line);
}
/*
int main()
{
	int		fd;
	int		l = 0;
	char	*line;

	fd = open("test.txt", O_RDONLY | O_CREAT);
	while (l < 5)
	{
		line = get_next_line(fd);
		printf("\n%i: %s", l, line);
	//	free(line);
		l++;
	}
	close (fd);
	return (0);
}
*/
