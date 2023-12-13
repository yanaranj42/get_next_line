/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:52:58 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/13 18:18:14 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buffer[i])
	{
		free(buffer);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	printf("%i\n", i);
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
	{
		line[j] = buffer[i];
		j++;
		i++;
	}
	free(buffer);
	return (line);
}

char	*ft_line(char *buffer)
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

char	*read_file(int fd, char *strg)
{
	char	*buffer;
	int		bytes;

	bytes = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (bytes > 0 && ft_strchr(buffer, '\n'))
	{
		bytes = read (fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			strg = ft_strjoin(strg, buffer);
			if (!strg)
				return (NULL);
		}
		else if (bytes < 0)
			return (ft_free(buffer, strg));
	}
//	free(buffer);
	return (strg);
}

char	*get_next_line(int fd)
{
	char	*strg;
	char	*line;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, strg);
	if (!line)
		return (NULL);
	line = ft_line(strg);
	strg = ft_next(strg);
	return (line);
}

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
		free(line);
		l++;
	}
	close (fd);
	return (0);
}
