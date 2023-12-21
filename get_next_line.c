/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:52:58 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/21 13:30:17 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
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
	if (buffer[i] == '\0')
		return (ft_free(&buffer, NULL));
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
		return (ft_free(&buffer, NULL));
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
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
	i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line) //add this protection
		return (ft_free(&buffer, NULL));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
		line[i] = '\n';
	line[++i] = '\0';	
	return (line);
}

static char	*read_file(int fd, char *strg)
{
	char	*buffer;
	int		bytes;

	if (!strg)
	{
		//strg = ft_calloc(1, 1);
		ft_free(&strg, NULL);
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (ft_free(&strg, NULL));
	bytes = 1;
	while (bytes > 0)
	{
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes = read (fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free(&buffer, &strg), NULL);
		if (bytes > 0)
		{
			buffer[bytes] = 0;
			strg = ft_strjoin(strg, buffer);
			if (!strg)
				return (NULL);
		}
	}
	return (ft_free(&buffer, NULL), strg);
}

char	*get_next_line(int fd)
{
	static char	*strg = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	strg = read_file(fd, strg);
	if (!strg)
		return (ft_free(&strg, NULL));
	line = ft_line(strg);
	if (!line)
		return (ft_free(&strg, NULL));
	strg = ft_next(strg);
	if (!strg)
		return (ft_free(&strg, NULL));
	return (line);
}
/*
int main()
{
	int		fd;
	char	*line;

	fd = open("lorem.txt", O_RDONLY | O_CREAT);
//	line = NULL;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s",line);
			ft_free(&line, NULL);
		}
		//ft_free(&line, NULL);
	}
	close (fd);
	return (0);
}*/
