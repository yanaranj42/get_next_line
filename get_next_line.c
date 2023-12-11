/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:01:11 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/11 15:04:56 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*Libera la memoria asignada en las cadenas.
 * Primero verifica su hay memoria asignada y luego la libera
*/
static char	*ft_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}
char	ft_line()
{
}
char	ft_next()
{
}


/* Leera la linea que encuentre en el FD y concatena las cadenas en el
 * STRG y devuelve el resultado de la cadena(strg).
 * *buf: almacena datos leido de manera temp.
 * byte: num de bytes que ira contando. Se inicia en 1 para entrar en
 *		 el bucle
 * malloc: para asignar memoria en el buf.
 * while(): bucle que busca el caracter '\n' o hasta el final de linea
 * 			primero lee los bytes desde el fd al BS
 * 			Si se leyeron, primero asegura que que no termina en nulo.
 * 			Concatena el buf. a una cadena existente y lo almacena en
 * 			strg. Si falla, return NULL.
 * 			Else (si no ha leido bytes), libera los datos.
 * Al salir del bucle, libera la memoria de buf despues de leer las lineas
 */
static char	*read_line(int fd, char *strg)
{
	char	*buf;
	int		bytes;

	byte = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free(NULL, strg));
	while (bytes > 0 && !ft_strchr(buf, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes > 0)
		{
			buf[bytes] = '\0';//iguala a nulo para que sea una cadena ok
			strg = ft_strjoin(strg, buf);
			if (!strg)
				return (NULL);
		}
		else if (bytes < 0)
			return (ft_free(strg, buf));
	}
	free(buf);
	return (strg);	
}

char	*get_next_line(int fd)
{
	static char	*strg = NULL;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	strg = read_line(fd, strg);
	if (!strg)
		return (NULL);
	line = ft_line(strg);
	strg = ft_next(strg);
	return (line);
}
