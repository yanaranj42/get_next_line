/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:52:58 by yanaranj          #+#    #+#             */
/*   Updated: 2024/02/08 12:55:50 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	i = 0;
	if (buffer[i] == '\0')
		return (ft_free(&buffer, NULL));
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!line)
		return (ft_free(&buffer, NULL));
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	ft_free(&buffer, NULL);
	return (line);
}

static char	*ft_line(char *strg)
{
	char	*line;
	int		i;

	i = 0;
	if (!strg[i])
		return (NULL);
	while (strg[i] && strg[i] != '\n')
		i++;
	if (strg[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (strg[i] && strg[i] != '\n')
	{
		line[i] = strg[i];
		i++;
	}
	if (strg[i] && strg[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*read_file(int fd, char *strg)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&strg, NULL));
	buffer[0] = '\0';
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read (fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free(&buffer, &strg));
		else if (bytes > 0)
		{
			buffer[bytes] = '\0';
			strg = ft_strjoin(strg, buffer);
			if (ft_strchr(buffer, '\n'))
				break ;
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
		return (NULL);
	line = ft_line(strg);
	if (!line)
		return (ft_free(&strg, NULL));
	strg = ft_next(strg);
	return (line);
}
